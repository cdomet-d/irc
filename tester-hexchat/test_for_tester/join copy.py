# -*- coding: UTF-8 -*-
import hexchat

__module_name__ = "Join"
__module_version__ = "1.0"
__module_description__ = "Tries to invite a client that already in the chan"

def join(word, word_eol, userdata):
	nick = hexchat.get_info("nick")
	if nick == "sweet":
		hexchat.command("JOIN")						#should send NOTENOUGHPARAMS but command blocked by hexchat
		hexchat.command("JOIN :#chan with space")	#sends "No such channel"
		hexchat.command("JOIN :#chan,")				#joins channel "chan"
		hexchat.command("JOIN #:chan")				#joins channel ":chan"
		hexchat.command("JOIN chan")				#sends "No such channel"
		hexchat.command("JOIN &chan")				#sends "No such channel"
		hexchat.command("MODE #chan +k pass")		#changes mode for following test function
	return hexchat.EAT_NONE

def joinPrivChan(word, word_eol, userdata):
	nick = hexchat.get_info("nick")
	if nick == "b":
		hexchat.command("JOIN #chan")			#sends "password required"
		hexchat.command("JOIN #chan wrongkey")	#sends "password required"
		hexchat.command("JOIN #chan pass")		#joins channel "chan"
		hexchat.command("JOIN #chan2")			#join channel "chan2"
		hexchat.command("JOIN #chan3")			#join channel "chan3"
		hexchat.command("MODE #chan3 +i")		#changes mode for following tests
		hexchat.command("INVITE a #chan3")
	return hexchat.EAT_NONE

hexchat.hook_command("NICK", join)
hexchat.hook_command("USER", joinPrivChan)
