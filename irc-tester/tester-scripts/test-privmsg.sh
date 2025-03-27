#!/bin/bash

rm -f outputs/client*

mkfifo outputs/client1_in outputs/client1_out
mkfifo outputs/client2_in.txt outputs/client2_out.txt
mkfifo outputs/client3_in.txt outputs/client3_out.txt

exec {client1_in_fd}<>outputs/client1_in
exec {client1_out_fd}<>outputs/client1_out
exec {client2_in_fd}<>outputs/client2_in.txt
exec {client2_out_fd}<>outputs/client2_out.txt
exec {client3_in_fd}<>outputs/client3_in.txt
exec {client3_out_fd}<>outputs/client3_out.txt

nc 0.0.0.0 4444 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!
nc 0.0.0.0 4444 0<&${client2_in_fd} 1>&${client2_out_fd} &
PID2=$!
nc 0.0.0.0 4444 0<&${client3_in_fd} 1>&${client3_out_fd} &
PID3=$!

sleep 0.2

# ➤ client1
cat <<EOF >&${client1_in_fd}
PRIVMSG
PASS 0
NICK chacham
USER c c c c
JOIN #chan
JOIN #chan1

EOF

sleep 0.5

# ➤ client2
cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b b b b
JOIN #chan
JOIN #chan1
EOF

sleep 0.5

# ➤ client3
cat <<EOF >&${client3_in_fd}
PASS 0
NICK juju
USER j j j j
EOF

sleep 0.5

# ➤ client1
cat <<EOF >&${client1_in_fd}
PRIVMSG
PRIVMSG bobby
PRIVMSG #chan
PRIVMSG dontexist hey
PRIVMSG #dontexist hey
PRIVMSG bobby :hey how are you
PRIVMSG bobby,juju hey
PRIVMSG #chan yo whats up
PRIVMSG #chan,#chan1 :hey how are you
PART #chan1
PRIVMSG #chan1 hey
EOF

sleep 0.5

echo "QUIT" >&${client1_in_fd}
echo "QUIT" >&${client2_in_fd}

sleep 3

kill $PID1 2>/dev/null
kill $PID2 2>/dev/null
kill $PID3 2>/dev/null

wait $PID1 2>/dev/null
wait $PID2 2>/dev/null
wait $PID3 2>/dev/null

cat outputs/client1_out > outputs/output.txt &
cat outputs/client2_out.txt >> outputs/output.txt &

sleep 0.5

exec {client1_in_fd}>&-
exec {client1_out_fd}>&-
exec {client2_in_fd}>&-
exec {client2_out_fd}>&-
exec {client3_in_fd}>&-
exec {client3_out_fd}>&-

rm -f outputs/client*


#TODO:
#If <target> is a channel name, it may be prefixed with one or more channel membership prefix character (@, +, etc) 
#and the message will be delivered only to the members of that channel with the given or higher status in the channel. 