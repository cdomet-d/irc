#!/bin/bash

rm -f outputs/client*

mkfifo outputs/client1_in.txt outputs/client1_out.txt
mkfifo outputs/client2_in.txt outputs/client2_out.txt

exec {client1_in_fd}<>outputs/client1_in.txt
exec {client1_out_fd}<>outputs/client1_out.txt
exec {client2_in_fd}<>outputs/client2_in.txt
exec {client2_out_fd}<>outputs/client2_out.txt

nc 0.0.0.0 4444 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!
nc 0.0.0.0 4444 0<&${client2_in_fd} 1>&${client2_out_fd} &
PID2=$!

sleep 0.2

#tests if channel name is valid + if correct JOIN messages are sent
# + tries using JOIN before registration 
cat <<EOF >&${client1_in_fd}
JOIN
JOIN #chan
PASS 0
NICK chacham
USER c c c c
JOIN
JOIN :#chan with space
JOIN :#chan,
JOIN #:chan
JOIN chan
JOIN &chan
JOIN #chan
MODE #chan +k key
EOF

sleep 0.5

#client2 tries to join #chan with no key and with the wrong key 
#see if client1 receives a message when client2 joins #chan
cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b b b b
JOIN #chan
JOIN #chan wrongkey
JOIN #chan key
JOIN #chan2
JOIN #chan3
MODE #chan3 +k key
EOF

sleep 0.5

#client1 joins several channels at once and tries to join #chan though he's already in it
cat <<EOF >&${client1_in_fd}
JOIN #chan2,#chan3,#chan ,key
MODE #chan +i
INVITE bobby #chan
EOF

sleep 0.5

#tests JOIN 0 + tests if having an invite makes key unnecessary
cat <<EOF >&${client2_in_fd}
JOIN 0
JOIN #chan
EOF

sleep 0.5

#client1 joins several channels at once and tries to join #chan though he's already in it
cat <<EOF >&${client1_in_fd}
INVITE bobby #chan
EOF

sleep 0.5

#tests JOIN 0 + tests if having an invite makes key unnecessary
cat <<EOF >&${client2_in_fd}
JOIN #chan
JOIN #chan key
PART #chan
EOF

sleep 0.5

#tests channel client limit
cat <<EOF >&${client1_in_fd}
MODE #chan -ik +l key 1
EOF

sleep 0.5

cat <<EOF >&${client2_in_fd}
JOIN #chan
EOF

sleep 0.5

echo "QUIT" >&${client1_in_fd}
echo "QUIT" >&${client2_in_fd}

sleep 3

kill $PID1 2>/dev/null
kill $PID2 2>/dev/null

wait $PID1 2>/dev/null
wait $PID3 2>/dev/null

cat outputs/client1_out.txt > outputs/output.txt &
cat outputs/client2_out.txt >> outputs/output.txt &

sleep 0.5

exec {client1_in_fd}>&-
exec {client1_out_fd}>&-
exec {client2_in_fd}>&-
exec {client2_out_fd}>&-

rm -f outputs/client*


#While a client is joined to a channel, 
#they receive all relevant information about that channel 
#including the JOIN, PART, KICK, and MODE messages affecting the channel.
#They receive all PRIVMSG and NOTICE messages sent to the channel, 
#and they also receive QUIT messages from other clients joined to the same channel

#TODO: mettre un client dans 50 channel pour avoir erreur ERR_TOOMANYCHANNELS