# -*- coding: UTF-8 -*-
# nickTesting.py
import hexchat

expected_message = "expected [AZ - az]"

def compReply(word, word_eol, userdata):
    # Server messages use word[3:] for the error text
    message = ' '.join(word[3:])  # Reconstruct full message
    if userdata in message:
        hexchat.prnt("\00303SUCCESS: Test: 'Illegal char'")
    else:
        hexchat.prnt("\00304FAILURE: Test: 'Illegal char'")
    return hexchat.EAT_NONE

def nickTest(word, word_eol, userdata):
	nick = hexchat.get_info("nick")
	if nick == "b":
		hexchat.command("NICK #cha")
		hexchat.command("NICK }cha")
		hexchat.command("NICK #cha")
		hexchat.command("NICK ::cha")
		hexchat.command("NICK 4cha")
		hexchat.command("NICK -cha")
		hexchat.command("NICK [cha")
		hexchat.command("NICK ]cha")
		hexchat.command("NICK \`cha")
		hexchat.command("NICK ^cha")
		hexchat.command("NICK {cha")
		hexchat.command("NICK }cha")
		hexchat.command("NICK +cha")
		hexchat.command("NICK cha$")
		hexchat.command("NICK cha#")
		hexchat.command("NICK cha:")
		hexchat.command("NICK chacham")
	return hexchat.EAT_NONE

hexchat.hook_server("001", nickTest)
hexchat.hook_server("432", compReply, userdata=expected_message)
