#!/bin/bash
hexchat --command="/ircserv 4444 0" &
HEXCHAT_PID=$!

# Wait for HexChat to initialize
sleep 3