# -*- coding: UTF-8 -*-
import hexchat

__module_name__ = "Nick"
__module_version__ = "1.0"
__module_description__ = "Nick testing"

def nickForbCharTesting(word, word_eol, userdata):
	channel = hexchat.get_info("channel")
	if channel == "#testnick":
		hexchat.command("NICK #cha")
		hexchat.command("NICK ::cha")
		hexchat.command("NICK 4cha")
		hexchat.command("NICK -cha")
		hexchat.command("NICK [cha")
		hexchat.command("NICK ]cha")
		hexchat.command("NICK \\cha")
		hexchat.command("NICK \`cha")
		hexchat.command("NICK ^cha")
		hexchat.command("NICK {cha")
		hexchat.command("NICK }cha")
		hexchat.command("NICK +cha")
		hexchat.command("NICK cha$")
		hexchat.command("NICK cha-[]\\^4\`{}")
		hexchat.command("NICK chacham sweet")
		hexchat.command("NICK cha#")
		hexchat.command("NICK cha:")
		hexchat.command("NICK :")
		hexchat.command("NICK sweet")
		return hexchat.EAT_NONE

hexchat.hook_print("Join", nickForbCharTesting)