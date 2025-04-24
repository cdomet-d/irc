# -*- coding: UTF-8 -*-
# join.py

import hexchat

expected_message = "You have not registered"

def compReply(word, word_eol, userdata):
    message = ' '.join(word[3:])
    if userdata in message:
        hexchat.prnt("\00303SUCCESS: Test: 'Nickname is already in use'")
    else:
        hexchat.prnt("\00304FAILURE: Test: 'Nickname is already in use'")
    return hexchat.EAT_NONE

def joinBeforeRegistration(word, word_eol, userdata):
	

hexchat.hook_server("001", joinBeforeRegistration)
hexchat.hook_server("433", compReply, userdata=expected_message)