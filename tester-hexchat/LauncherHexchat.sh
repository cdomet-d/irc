#!/bin/bash
# Launch HexChat with a specific configuration
hexchat --command="/ircserv 4444 0" &
HEXCHAT_PID=$!

# Wait for HexChat to initialize
sleep 3  # Adjust delay as needed

# Send commands via Python script
python3 launcher.py
