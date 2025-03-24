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
NICK cha-[]\^{}4\`
USER c c c c
NICK chacham sweet
NICK cha#
NICK cha:
EOF

timeout 2s nc 0.0.0.0 4444 < test_input.txt > output.txt

#TODO: faire un test avec deux client pour essayer d'attribuer un nickname deja pris
#TODO: tester sur libera chat "NICK :"
#TODO: mettre le client dans un channel, changer son nickname et voir si le message est envoye a tout le channel