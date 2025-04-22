# -*- coding: UTF-8 -*-
import hexchat

__module_name__ = "Who"
__module_version__ = "1.0"
__module_description__ = "Tries WHO command with different parameters"

def whoTesting(word, word_eol, userdata):
	channel = hexchat.get_info("channel")
	if channel == "#testwho":
		hexchat.command("WHO")
		hexchat.command("who #testwho")
		hexchat.command("who #testwho vfik")
		hexchat.command("quit")

hexchat.hook_print("Join", whoTesting)
