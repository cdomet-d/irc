#!/bin/bash

# Fichier contenant les commandes à envoyer
#registration test
cat <<EOF > test_input.txt
USER c c c c
NICK chacham
PASS wrongpassword
PASS 0
PASS fff
USER c c c c
NICK alex
NICK alex
PASS 0
USER c c c c
EOF

# Envoi des commandes à l'IRC server et capture de la réponse
nc 0.0.0.0 4444 < test_input.txt > output.txt


# Préparation des fichiers de commandes pour les deux clients
cat <<EOF > client1_input.txt
USER user1 u u u
NICK alpha
PASS 1234
EOF

cat <<EOF > client2_input.txt
USER user2 u u u
NICK beta
PASS 5678
EOF

# Lancement des deux clients en parallèle
# Chaque client écrit sa sortie dans un fichier différent

nc 0.0.0.0 4444 < client1_input.txt > client1_output.txt &
PID1=$!

nc 0.0.0.0 4444 < client2_input.txt > client2_output.txt &
PID2=$!

# Attente que les deux clients aient terminé
wait $PID1
wait $PID2

