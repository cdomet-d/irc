#!/bin/bash

rm -f outputs/client*

mkfifo outputs/client1_in outputs/client1_out
mkfifo outputs/client2_in.txt outputs/client2_out.txt

exec {client1_in_fd}<>outputs/client1_in
exec {client1_out_fd}<>outputs/client1_out
exec {client2_in_fd}<>outputs/client2_in.txt
exec {client2_out_fd}<>outputs/client2_out.txt

nc 0.0.0.0 6667 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!
nc 0.0.0.0 6667 0<&${client2_in_fd} 1>&${client2_out_fd} &
PID2=$!

sleep 0.2

#+itkol

cat <<EOF >&${client1_in_fd}
MODE
PASS 0
NICK chacham
USER c 0 * c
JOIN #chan
MODE
MODE +i
MODE wrongchan
MODE #dontexist
MODE #chan
MODE #chan k-t
MODE #chan u
EOF

sleep 0.5

cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b 0 * b
JOIN #chan
MODE #chan
MODE #chan +i
EOF

sleep 0.5

cat <<EOF >&${client1_in_fd}
MODE #chan +ikol-t password bobby 2
EOF

sleep 0.5

cat <<EOF >&${client2_in_fd}
MODE #chan +t
EOF

sleep 0.5

cat <<EOF >&${client1_in_fd}
MODE #chan -ikol bobby
MODE #chan +k
MODE #chan +k key
MODE #chan +k keyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
MODE #chan +l
MODE #chan +l -10
MODE #chan +l hehehe
MODE #chan +o dontexist
MODE #chan -o dontexist
KICK #chan bobby
MODE #chan +o bobby
MODE #chan +i-i he he
QUIT
EOF

sleep 0.5

echo "QUIT" >&${client2_in_fd}

sleep 3

kill $PID1 2>/dev/null
kill $PID2 2>/dev/null

wait $PID1 2>/dev/null
wait $PID2 2>/dev/null

cat outputs/client1_out > outputs/output.txt &
sleep 1
cat outputs/client2_out.txt >> outputs/output.txt &

sleep 2

exec {client1_in_fd}>&-
exec {client1_out_fd}>&-
exec {client2_in_fd}>&-
exec {client2_out_fd}>&-

rm -f outputs/client*