#!/bin/bash

#NICK
cat <<EOF > test_input.txt
PASS 0
NICK
NICK :charlotte sweeting
NICK #cha
NICK ::cha
NICK 4cha
NICK -cha
NICK [cha
NICK ]cha
NICK \cha
NICK \`cha
NICK ^cha
NICK {cha
NICK }cha
NICK +cha
NICK cha$
NICK cha-[]\^4\`{}
USER c c c c
NICK chacham sweet
NICK cha#
NICK cha:
NICK :
JOIN #chan
NICK sweet
EOF

cat << EOF > client2_input.txt
PASS 0
NICK chacham
NICK bobby
USER b b b b
JOIN #chan
EOF

timeout 2s nc 0.0.0.0 4444 < test_input.txt > output.txt & PID1=$!

timeout 2s nc 0.0.0.0 4444 < client2_input.txt > client2_output.txt & PID2=$!

wait $PID1
wait $PID2

cat client2_output.txt >> output.txt

#TODO: mettre le client dans un channel, changer son nickname et voir si le message est envoye a tout le channel