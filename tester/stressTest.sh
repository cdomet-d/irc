#!/bin/bash

SERVER="0.0.0.0"
PORT="6667"  # Default IRC port
PASSWORD="0"
CHANNEL="#test"
NUM_CLIENTS=500
MESSAGE_DELAY=0.1  # Seconds between messages

# Nickname generator (a-z, aa-zz, aaa-zzz, etc)
generate_nick() {
    local chars=( {a..z} )
    local count=$1 length=1
    
    while true; do
        for ((i=0; i<${#chars[@]}; i++)); do
            printf "%${length}s" | sed "s/ /${chars[i]}/g"
            ((count--))
            [[ $count -le 0 ]] && return
        done
        ((length++))
    done
}

# Launch clients
for ((i=0; i<NUM_CLIENTS; i++)); do
    nick=$(generate_nick $((i+1)) | head -n1)
    
    (
        # Connection and authentication
        printf "PASS %s\r\n" "$PASSWORD"
        printf "NICK %s\r\n" "$nick"
        printf "USER %s 0 * :%s\r\n" "$nick" "$nick"
        
        # Join channel and message loop
        printf "JOIN %s\r\n" "$CHANNEL"
        while true; do
            sleep $MESSAGE_DELAY
            printf "PRIVMSG %s :Stress test from %s\r\n" "$CHANNEL" "$nick"
        done
    ) | nc -C $SERVER $PORT &
    
    # Rate limiting to prevent system overload
    if (( i % 100 == 0 )); then
        sleep 0.5
    fi
done

echo "Launched $NUM_CLIENTS clients. Press Ctrl+C to stop."
wait
