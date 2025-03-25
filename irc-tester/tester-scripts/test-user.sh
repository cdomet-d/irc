#!/bin/bash

rm -f client*

mkfifo client1_in client1_out

exec {client1_in_fd}<>client1_in
exec {client1_out_fd}<>client1_out

nc 0.0.0.0 4444 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!

sleep 0.2

cat <<EOF >&${client1_in_fd}
PASS 0
NICK chacham
USER
USER c
USER c c
USER c c c
USER c c c c
USER :c c
USER c c c c :hello world
USER c c c c 
QUIT
EOF

sleep 3

kill $PID1 2>/dev/null

wait $PID1 2>/dev/null

cat client1_out > output.txt &

sleep 0.5

exec {client1_in_fd}>&-
exec {client1_out_fd}>&-

rm -f client*

#TODO: add limit to username ?

#TODO: oblige 0 and * for hostname and servername ?
#Note that hostname and servername are normally ignored by the IRC
#   server when the USER command comes from a directly connected client
#   (for security reasons), but they are used in server to server
#   communication.