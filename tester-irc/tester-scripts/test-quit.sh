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

cat <<EOF >&${client1_in_fd}
PASS 0
NICK chacham
USER c 0 * c
JOIN #chan
EOF

sleep 0.5

cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b 0 * b
JOIN #chan
EOF

sleep 0.5

#tests if clients receive appropriate messages
echo "QUIT :bye bye" >&${client1_in_fd}
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

#tests if QUIT works during registration
cat <<EOF > test_input.txt
QUIT
EOF

timeout 2s nc 0.0.0.0 4444 < test_input.txt >> outputs/output.txt


#TODO:
#When connections are terminated by a client-sent QUIT command, 
#servers SHOULD prepend <reason> with the ASCII string "Quit: " 
#when sending QUIT messages to other clients, to represent that this user terminated the connection themselves. 
#This applies even if <reason> is empty, 
#in which case the reason sent to other clients SHOULD be just this "Quit: " string. 
#However, clients SHOULD NOT change behaviour based on the prefix of QUIT message reasons, as this is not required behaviour from servers.

#If a client connection is closed without the client issuing a QUIT command to the server, 
#the server MUST distribute a QUIT message to other clients informing them of this, 
#distributed in the same was an ordinary QUIT message. 
#Servers MUST fill <reason> with a message reflecting the nature of the event which caused it to happen. 
#For instance, "Ping timeout: 120 seconds", "Excess Flood", and "Too many connections from this IP" are examples of relevant reasons for closing or for a connection with a client to have been closed.