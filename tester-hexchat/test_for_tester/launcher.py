def connect_and_commands():
	# Wait for HexChat to fully initialize
	time.sleep(5)  # Adjust based on your system

	# Connect to server
	hexchat.command("CONNECT your.irc.server.com")

	# Wait for connection
	time.sleep(3)  # Adjust based on server response time

	# Send commands
	hexchat.command("NICK YourBotNick")
	hexchat.command("JOIN #yourchannel")
	hexchat.command("PRIVMSG #yourchannel :Hello, automated message!")

# Hook the "Welcome" message (IRC 001) to trigger commands
def on_connect(word, word_eol, userdata):
    hexchat.command("JOIN #yourchannel")
    return hexchat.EAT_NONE

hexchat.hook_server("001", on_connect)  # Triggers after successful connection

# Run initial setup
connect_and_commands()