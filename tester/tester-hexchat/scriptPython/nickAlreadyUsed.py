# -*- coding: UTF-8 -*-
# nickAlreadyUsed.py
import hexchat

expected_message = "Nickname is already in use"

def compReply(word, word_eol, userdata):
    message = ' '.join(word[3:])
    if userdata in message:
        hexchat.prnt("\00303SUCCESS: Test: 'Nickname is already in use'")
    else:
        hexchat.prnt("\00304FAILURE: Test: 'Nickname is already in use'")
    return hexchat.EAT_NONE

def triggerNickChange(word, word_eol, userdata):
	current_nick = hexchat.get_info("nick")
	if current_nick == "c":
		hexchat.command("NICK chacham")
	return hexchat.EAT_NONE

hexchat.hook_server("001", triggerNickChange)
hexchat.hook_server("433", compReply, userdata=expected_message)
