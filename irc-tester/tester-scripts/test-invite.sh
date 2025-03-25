#!/bin/bash

# Nettoyage si des FIFOs sont déjà là
rm -f client*

# Création des pipes nommés
mkfifo client1_in client1_out
mkfifo client2_in client2_out
mkfifo client3_in client3_out

# Ouvrir les FIFOs avec des descripteurs de fichiers dynamiques
exec {client1_in_fd}<>client1_in
exec {client1_out_fd}<>client1_out
exec {client2_in_fd}<>client2_in
exec {client2_out_fd}<>client2_out
exec {client3_in_fd}<>client3_in
exec {client3_out_fd}<>client3_out

# Lancer les clients (en lecture/écriture FIFO)
nc 0.0.0.0 4444 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!
nc 0.0.0.0 4444 0<&${client2_in_fd} 1>&${client2_out_fd} &
PID2=$!
nc 0.0.0.0 4444 0<&${client3_in_fd} 1>&${client3_out_fd} &
PID3=$!

sleep 0.2  # Laisser le temps aux connexions de se faire

# ➤ client1
cat <<EOF >&${client1_in_fd}
PASS 0
NICK chacham
USER c c c c
JOIN #chan
MODE #chan +i
EOF

sleep 0.5

# ➤ client2
cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b b b b
JOIN #chan
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
INVITE
INVITE dontexist #chan
INVITE bobby #dontexist
INVITE bobby wrongchan
INVITE bobby #chan
EOF

sleep 0.5

# ➤ client2
cat <<EOF >&${client2_in_fd}
JOIN #chan
INVITE juju #chan
EOF

sleep 0.5

# ➤ client1
cat <<EOF >&${client1_in_fd}
INVITE bobby #chan
MODE #chan -i
EOF

sleep 0.5

# ➤ client2
cat <<EOF >&${client2_in_fd}
INVITE juju #chan
PART #chan
INVITE juju #chan
EOF

sleep 0.5

# Quit pour les deux clients
echo "QUIT" >&${client1_in_fd}
echo "QUIT" >&${client2_in_fd}
echo "QUIT" >&${client3_in_fd}

sleep 3  # Laisser le serveur envoyer les réponses

# Arrêter les processus nc
kill $PID1 2>/dev/null
kill $PID2 2>/dev/null
kill $PID3 2>/dev/null

# Attendre que les processus se terminent
wait $PID1 2>/dev/null
wait $PID2 2>/dev/null
wait $PID3 2>/dev/null

# Récupérer les logs depuis les FIFOs vers un fichier de sortie
cat client1_out > output.txt &
cat client2_out >> output.txt &

sleep 0.5

# Nettoyer les FIFOs et autres fichiers temporaires
exec {client1_in_fd}>&-
exec {client1_out_fd}>&-
exec {client2_in_fd}>&-
exec {client2_out_fd}>&-
exec {client3_in_fd}>&-
exec {client3_out_fd}>&-

rm -f client*

trap cleanup EXIT