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
timeout --preserve-status -s SIGKILL 5s nc 0.0.0.0 4444 0<&${client2_in_fd} 1>&${client2_out_fd}
PID1=$!
timeout --preserve-status -s SIGKILL 5s nc 0.0.0.0 4444 0<&${client2_in_fd} 1>&${client2_out_fd}
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

sleep 1.5  # Laisser le serveur envoyer les réponses

# Envoyer EOF aux pipes d'entrée
exec {client1_in_fd}>&-
exec {client2_in_fd}>&-

# Fermer les clients proprement en tuant les processus netcat (nc)
kill $PID1 2>/dev/null || true  # Éviter erreur si déjà fermé
kill $PID2 2>/dev/null || true

# Attendre que les processus se ferment complètement (optionnel)
wait $PID1 2>/dev/null || true 
wait $PID2 2>/dev/null || true 

# Vérifier si les processus sont encore en vie
if ps -p $PID1 > /dev/null || ps -p $PID2 > /dev/null; then
    echo "Les processus nc sont toujours en vie. Tentative de les tuer..."
    kill -9 $PID1 $PID2 2>/dev/null || true
fi

# Récupérer les logs depuis les FIFOs vers un fichier de sortie
cat client1_out > output.txt
cat client2_out >> output.txt

# Nettoyer les FIFOs et autres fichiers temporaires
exec {client1_out_fd}>&-
exec {client2_out_fd}>&-
rm -f client*


#TODO: mettre le client dans un channel, changer son nickname et voir si le message est envoye a tout le channel

#echo "QUIT" >&${client1_in_fd}
#echo "QUIT" >&${client2_in_fd}
