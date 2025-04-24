# -*- coding: UTF-8 -*-
# user.py
import hexchat

expected_message = "You may not reregister"

def compReply(word, word_eol, userdata):
    message = ' '.join(word[3:])
    if userdata in message:
        hexchat.prnt("\00303SUCCESS: Test: 'Double registration'")
    else:
        hexchat.prnt("\00304FAILURE: Test: 'Double registration'")
    return hexchat.EAT_NONE

def doubleRegistration(word, word_eol, userdata):
	current_nick = hexchat.get_info("nick")
	if current_nick == "b":
		hexchat.command("USER")
	return hexchat.EAT_NONE

hexchat.hook_server("001", doubleRegistration)
hexchat.hook_server("462", compReply, userdata=expected_message)
