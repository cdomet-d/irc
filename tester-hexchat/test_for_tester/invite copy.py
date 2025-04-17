# -*- coding: UTF-8 -*-
import hexchat

__module_name__ = "Invite"
__module_version__ = "1.0"
__module_description__ = "Tries to invite a client that already in the chan"

def inviting(word, word_eol, userdata):
	channel = hexchat.get_info("channel")
	if channel == "#testinvite":
		hexchat.command("invite c #test")
		return hexchat.EAT_NONE

hexchat.hook_print("Join", inviting)
