#!/bin/bash

rm -f outputs/client*

mkfifo outputs/client1_in outputs/client1_out
mkfifo outputs/client2_in.txt outputs/client2_out.txt

exec {client1_in_fd}<>outputs/client1_in
exec {client1_out_fd}<>outputs/client1_out
exec {client2_in_fd}<>outputs/client2_in.txt
exec {client2_out_fd}<>outputs/client2_out.txt

nc 0.0.0.0 4444 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!
nc 0.0.0.0 4444 0<&${client2_in_fd} 1>&${client2_out_fd} &
PID2=$!

sleep 0.2

#tries PART before registration
#tries PART with wrong params
#parts from several channels at once with a comment
#tests if channel is correctly deleted if all clients leave
cat <<EOF >&${client1_in_fd}
PART
PASS 0
NICK chacham
USER c 0 * c
PART
PART #dontexist
PART wrongchan
JOIN #chan,#chan2,#chan3
PART #chan
JOIN #chan
EOF

sleep 0.5

#tries to part from a channel he isn't in
#succedes to part from chan, client1 should receive appropriate message
cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b 0 * b
PART #chan
JOIN #chan,#chan2,#chan3
PART #chan,#chan2,#chan3 :im leaving. idiots.
EOF

sleep 0.5

echo "QUIT" >&${client1_in_fd}
echo "QUIT" >&${client2_in_fd}

sleep 3

kill $PID1 2>/dev/null
kill $PID2 2>/dev/null

wait $PID1 2>/dev/null
wait $PID2 2>/dev/null

cat outputs/client1_out > outputs/output.txt &
cat outputs/client2_out.txt >> outputs/output.txt &

sleep 2

exec {client1_in_fd}>&-
exec {client1_out_fd}>&-
exec {client2_in_fd}>&-
exec {client2_out_fd}>&-

rm -f outputs/client*