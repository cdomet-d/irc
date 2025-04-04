#!/bin/bash

# Configuration
SERVER="localhost"
PORT=4444
CHANNEL="#youpi"
CLIENT_COUNT=200

# Function to create a single client
create_client() {
  local i=$1
  {
    echo "PASS 0"
    echo "NICK USER$i"
    echo "USER USER_$i 0 * realname"
    echo "JOIN $CHANNEL"
    sleep 10 # Keep the connection alive for testing purposes
  } | nc $SERVER $PORT &
}

# Main loop to spawn clients
for ((i=1; i<=CLIENT_COUNT; i++)); do
  create_client $i
done

# Wait for all background processes to finish
wait

echo "Stress test completed with $CLIENT_COUNT clients." > result.log &