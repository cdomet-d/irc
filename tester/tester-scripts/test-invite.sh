#!/bin/bash

# Nettoyage si des FIFOs sont déjà là
rm -f outputs/client*

# Création des pipes nommés
mkfifo outputs/client1_in.txt outputs/client1_out.txt
mkfifo outputs/client2_in.txt outputs/client2_out.txt
mkfifo outputs/client3_in.txt outputs/client3_out.txt

# Ouvrir les FIFOs avec des descripteurs de fichiers dynamiques
exec {client1_in_fd}<>outputs/client1_in.txt
exec {client1_out_fd}<>outputs/client1_out.txt
exec {client2_in_fd}<>outputs/client2_in.txt
exec {client2_out_fd}<>outputs/client2_out.txt
exec {client3_in_fd}<>outputs/client3_in.txt
exec {client3_out_fd}<>outputs/client3_out.txt

# Lancer les clients (en lecture/écriture FIFO)
nc 0.0.0.0 4444 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!
nc 0.0.0.0 4444 0<&${client2_in_fd} 1>&${client2_out_fd} &
PID2=$!
nc 0.0.0.0 4444 0<&${client3_in_fd} 1>&${client3_out_fd} &
PID3=$!

sleep 0.2  # Laisser le temps aux connexions de se faire

# ➤ client1
#tries using INVITE before registration
cat <<EOF >&${client1_in_fd}
INVITE cc cc
INVITE
PASS 0
NICK chacham
USER c 0 * c
JOIN #chan
MODE #chan +i
EOF

sleep 0.5

# ➤ client2
#tries to join #chan without an invite
cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b 0 * b
JOIN #chan
EOF

sleep 0.5

# ➤ client3
cat <<EOF >&${client3_in_fd}
PASS 0
NICK juju
USER j 0 * j
EOF

sleep 0.5

# ➤ client1
#tries using INVITE with incorrect parameters
cat <<EOF >&${client1_in_fd}
INVITE #chan
INVITE dontexist #chan
INVITE bobby #dontexist
INVITE dontexist #dontexist
INVITE bobby #chan
EOF

sleep 0.5

# ➤ client2
#tries inviting someone but isn't an operator (with mode +i on #chan)
cat <<EOF >&${client2_in_fd}
INVITE
JOIN #chan
INVITE juju #chan
EOF

sleep 0.5

# ➤ client1
#invites bobby again even though he's already on #chan
cat <<EOF >&${client1_in_fd}
INVITE bobby #chan
MODE #chan -i
EOF

sleep 0.5

# ➤ client2
#tries inviting someone but isn't an operator (without mode +i on #chan)
#tries inviting someone but isn't on #chan
cat <<EOF >&${client2_in_fd}
INVITE juju #chan
PART #chan
INVITE juju #chan
EOF

sleep 0.5

# Quit pour les deux clients
echo "QUIT" >&${client1_in_fd}
sleep 0.5
echo "QUIT" >&${client2_in_fd}
sleep 0.5
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
cat outputs/client1_out.txt > outputs/output.txt &
sleep 1
cat outputs/client2_out.txt >> outputs/output.txt &

sleep 2

# Nettoyer les FIFOs et autres fichiers temporaires
exec {client1_in_fd}>&-
exec {client1_out_fd}>&-
exec {client2_in_fd}>&-
exec {client2_out_fd}>&-
exec {client3_in_fd}>&-
exec {client3_out_fd}>&-

rm -f outputs/client*
