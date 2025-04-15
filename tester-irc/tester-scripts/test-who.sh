#!/bin/bash

# Nettoyage si des FIFOs sont déjà là
rm -f outputs/client*


# Création des pipes nommés
mkfifo outputs/client1_in.txt outputs/client1_out.txt
mkfifo outputs/client2_in.txt outputs/client2_out.txt

# Ouvrir les FIFOs avec des descripteurs de fichiers dynamiques
exec {client1_in_fd}<>outputs/client1_in.txt
exec {client1_out_fd}<>outputs/client1_out.txt
exec {client2_in_fd}<>outputs/client2_in.txt
exec {client2_out_fd}<>outputs/client2_out.txt

# Lancer les clients (en lecture/écriture FIFO)
nc 0.0.0.0 4444 0<&${client1_in_fd} 1>&${client1_out_fd} &
PID1=$!
nc 0.0.0.0 4444 0<&${client2_in_fd} 1>&${client2_out_fd} &
PID2=$!

sleep 0.2  # Laisser le temps aux connexions de se faire

# ➤ Envoyer les lignes à client1
cat <<EOF >&${client1_in_fd}
who
pass 0
user c 0 * c
nick cha
join #chan
who
who #chan
who #chan k
EOF

sleep 0.5

# ➤ Envoyer à client2
cat <<EOF >&${client2_in_fd}
PASS 0
NICK bobby
USER b 0 * b
join #chan
who #chan
who #chan o
EOF

sleep 0.5

# Quit pour les deux clients
echo "QUIT" >&${client1_in_fd}
sleep 0.5
echo "QUIT" >&${client2_in_fd}

sleep 3  # Laisser le serveur envoyer les réponses

# Arrêter les processus nc
kill $PID1 2>/dev/null
kill $PID2 2>/dev/null

# Attendre que les processus se terminent
wait $PID1 2>/dev/null
wait $PID2 2>/dev/null

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

rm -f outputs/client*
