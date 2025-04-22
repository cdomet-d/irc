# -*- coding: UTF-8 -*-
import hexchat

__module_name__ = "Join"
__module_version__ = "1.0"
__module_description__ = "Tries to invite a client that already in the chan"

def join(word, word_eol, userdata):
	channel = hexchat.get_info("channel")
	if channel == "#testjoin":
		hexchat.command("JOIN")
		hexchat.command("JOIN :#chan with space")
		hexchat.command("JOIN :#chan,")
		hexchat.command("JOIN #:chan")
		hexchat.command("JOIN chan")
		hexchat.command("JOIN &chan")
		hexchat.command("MODE #chan +k password")
