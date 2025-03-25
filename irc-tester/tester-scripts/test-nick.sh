#!/bin/bash

# Nettoyage si des FIFOs sont déjà là
rm -f client*

# Création des pipes nommés
mkfifo client1_in client1_out
mkfifo client2_in client2_out

# Ouvrir les FIFOs avec des descripteurs de fichiers dynamiques
exec {client1_in_fd}<>client1_in
exec {client1_out_fd}<>client1_out
exec {client2_in_fd}<>client2_in
exec {client2_out_fd}<>client2_out

# Lancer les clients (en lecture/écriture FIFO)
nc 0.0.0.0 4444 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!
nc 0.0.0.0 4444 0<&${client2_in_fd} 1>&${client2_out_fd} &
PID2=$!

sleep 0.2  # Laisser le temps aux connexions de se faire

# ➤ Envoyer les lignes à client1
cat <<EOF >&${client1_in_fd}
PASS 0
NICK
NICK :charlotte sweeting
NICK #cha
NICK ::cha
NICK 4cha
NICK -cha
NICK [cha
NICK ]cha
NICK \\cha
NICK \`cha
NICK ^cha
NICK {cha
NICK }cha
NICK +cha
NICK cha$
NICK cha-[]\\^4\`{}
USER c c c c
NICK chacham sweet
NICK cha#
NICK cha:
NICK :
EOF

sleep 0.5

# ➤ Envoyer à client2
cat <<EOF >&${client2_in_fd}
PASS 0
NICK chacham
NICK bobby
USER b b b b
JOIN #chan
EOF

sleep 0.5

# ➤ Join pour les deux clients
echo "JOIN #chan" >&${client1_in_fd}
echo "JOIN #chan" >&${client2_in_fd}

sleep 0.5

# ➤ client1 change de nick
echo "NICK sweet" >&${client1_in_fd}

# Quit pour les deux clients
echo "QUIT" >&${client1_in_fd}
echo "QUIT" >&${client2_in_fd}

sleep 3  # Laisser le serveur envoyer les réponses

# Arrêter les processus nc
kill $PID1 2>/dev/null
kill $PID2 2>/dev/null

# Attendre que les processus se terminent
wait $PID1 2>/dev/null
wait $PID2 2>/dev/null

# Récupérer les logs depuis les FIFOs vers un fichier de sortie
cat client1_out > output.txt &
cat client2_out >> output.txt &

# Nettoyer les FIFOs et autres fichiers temporaires
exec {client1_in_fd}>&-
exec {client1_out_fd}>&-
exec {client2_in_fd}>&-
exec {client2_out_fd}>&-

rm -f client*

trap cleanup EXIT