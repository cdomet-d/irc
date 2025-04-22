# -*- coding: UTF-8 -*-
import hexchat

__module_name__ = "testiiiiing"
__module_version__ = "1.0"
__module_description__ = "testiiiiing testing"

def trytest(word, word_eol, userdata):
	hexchat.command("NICK sweet")
	return hexchat.EAT_NONE

def trytest2(word, word_eol, userdata):
	hexchat.command("JOIN #test")
	return hexchat.EAT_NONE

def trytest3(word, word_eol, userdata):
	channel = hexchat.get_info("channel")
	if channel == "#test":
		hexchat.command("PART #test")
	return hexchat.EAT_NONE

hexchat.hook_server("001", trytest)
hexchat.hook_command("NICK", trytest2)
hexchat.hook_server("315", trytest3)