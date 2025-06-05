#!/bin/bash
hexchat --command="/ircserv 6667 0" &
HEXCHAT_PID=$!

# Wait for HexChat to initialize
sleep 3