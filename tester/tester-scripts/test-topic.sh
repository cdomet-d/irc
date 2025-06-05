#!/bin/bash

rm -f outputs/client*

mkfifo outputs/client1_in.txt outputs/client1_out.txt
mkfifo outputs/client2_in.txt outputs/client2_out.txt

exec {client1_in_fd}<>outputs/client1_in.txt
exec {client1_out_fd}<>outputs/client1_out.txt
exec {client2_in_fd}<>outputs/client2_in.txt
exec {client2_out_fd}<>outputs/client2_out.txt

nc 0.0.0.0 6667 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!
nc 0.0.0.0 6667 0<&${client2_in_fd} 1>&${client2_out_fd} &
PID2=$!

sleep 0.2

#client1
#tests topic before registration and with wrong params
cat <<EOF >&${client1_in_fd}
TOPIC
PASS 0
NICK chacham
USER c 0 * c
JOIN #chan
TOPIC
TOPIC #dontexist
TOPIC wrongchan
TOPIC #chan :my sublime self
MODE #chan +t
EOF

sleep 0.5

#client2
#does topic but is not on channel
#tries to change it but is not an operator (chan has +t)
cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b 0 * b
TOPIC #chan
TOPIC #chan pizza
JOIN #chan
TOPIC #chan
TOPIC #chan lol
TOPIC #chan,#chan2 lol
EOF

#TODO: split sur les virgules peu importe si l'argument attends une liste ?
sleep 0.5

#client1
cat <<EOF >&${client1_in_fd}
MODE #chan -t
EOF

sleep 0.5

#client2
#should be able to change it caus mode t was removed
#TODO: third command should clear the topic
cat <<EOF >&${client2_in_fd}
TOPIC #chan lol
TOPIC #chan
TOPIC #chan :
TOPIC #chan
EOF

sleep 0.5

echo "QUIT" >&${client1_in_fd}
sleep 0.5
echo "QUIT" >&${client2_in_fd}

sleep 3

kill $PID1 2>/dev/null
kill $PID2 2>/dev/null

wait $PID1 2>/dev/null
wait $PID3 2>/dev/null

cat outputs/client1_out.txt > outputs/output.txt &
sleep 1
cat outputs/client2_out.txt >> outputs/output.txt &

sleep 2

exec {client1_in_fd}>&-
exec {client1_out_fd}>&-
exec {client2_in_fd}>&-
exec {client2_out_fd}>&-

rm -f outputs/client*