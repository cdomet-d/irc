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

#tries KICK before registration and with wrong params
cat <<EOF >&${client1_in_fd}
KICK
PASS 0
NICK chacham
USER c c c c
JOIN #chan
KICK
KICK wrongchan dontexist
KICK #chan dontexist
EOF

sleep 0.5

#tries to kick but isn't in channel
cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b b b b
KICK #chan chacham
EOF

sleep 0.5

# ➤ client3
cat <<EOF >&${client3_in_fd}
PASS 0
NICK juju
USER j j j j
JOIN #chan
EOF

sleep 0.5

#tries to kick someone who is not on the channel
#tries to kick someone from a non valid chan but valid target
cat <<EOF >&${client1_in_fd}
KICK #chan bobby
KICK wrongchan bobby
EOF

sleep 0.5

#tries to kick but isn't an operator
cat <<EOF >&${client2_in_fd}
JOIN #chan
KICK juju
KICK #chan juju
EOF

sleep 0.5

#kicks several people without a comment
cat <<EOF >&${client1_in_fd}
KICK #chan bobby,juju,dontexist
EOF

sleep 0.5

cat <<EOF >&${client2_in_fd}
JOIN #chan
EOF

sleep 0.5

#kicks someone with a comment
cat <<EOF >&${client1_in_fd}
KICK #chan bobby :baddly behaved
EOF

sleep 0.5

echo "QUIT" >&${client1_in_fd}
echo "QUIT" >&${client2_in_fd}
echo "QUIT" >&${client3_in_fd}

sleep 3

kill $PID1 2>/dev/null
kill $PID2 2>/dev/null
kill $PID3 2>/dev/null

wait $PID1 2>/dev/null
wait $PID2 2>/dev/null
wait $PID3 2>/dev/null

cat outputs/client1_out.txt > outputs/output.txt &
cat outputs/client2_out.txt >> outputs/output.txt &

sleep 2

exec {client1_in_fd}>&-
exec {client1_out_fd}>&-
exec {client2_in_fd}>&-
exec {client2_out_fd}>&-
exec {client3_in_fd}>&-
exec {client3_out_fd}>&-

rm -f outputs/client*


#Servers MAY limit the number of target users per KICK command via the TARGMAX parameter of RPL_ISUPPORT,
#and silently drop targets if the number of targets exceeds the limit.
#TODO: addtarget limit ??