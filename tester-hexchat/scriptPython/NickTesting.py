# -*- coding: UTF-8 -*-
import hexchat

__module_name__ = "Nick"
__module_version__ = "1.0"
__module_description__ = "Nick testing"

expected_message = "#cha: illegal first char: expected [AZ - az], is # :Erroneous nickname or username"

def compReply(word, word_eol, userdata):
	message = word_eol[2]  # Full message text (for most events)

	if userdata in message:
	    print("\00303SUCCESS: Server sent expected message!")
	else:
	    print("\00304FAILURE: Unexpected message received")
	return hexchat.EAT_NONE

def nickTest(word, word_eol, userdata):
	hexchat.command("NICK #cha")
	return hexchat.EAT_NONE

hexchat.hook_server("001", nickTest)
hexchat.hook_server("432", compReply, userdata=expected_message)