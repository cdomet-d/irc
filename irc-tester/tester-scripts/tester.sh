#!/bin/bash

# Préparation des fichiers de commandes pour les deux clients
#cat <<EOF > client1_input.txt
#USER user1 u u u
#NICK alpha
#PASS 1234
#EOF
#
#cat <<EOF > client2_input.txt
#USER user2 u u u
#NICK beta
#PASS 5678
#EOF

# Lancement des deux clients en parallèle
# Chaque client écrit sa sortie dans un fichier différent

#nc 0.0.0.0 4444 < client1_input.txt > client1_output.txt &
#PID1=$!
#
#nc 0.0.0.0 4444 < client2_input.txt > client2_output.txt &
#PID2=$!

# Attente que les deux clients aient terminé
#wait $PID1
#wait $PID2

