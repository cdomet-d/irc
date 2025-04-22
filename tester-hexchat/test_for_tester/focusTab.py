# -*- coding: UTF-8 -*-
import hexchat

__module_name__ = "Focus Tab"
__module_version__ = "1.0"
__module_description__ = "Trying to understand internal event of fucking HexChat"


def on_focus_tab(word, word_eol, userdata):
    print("Tab focused! Channel:", hexchat.get_info("channel"))
    return hexchat.EAT_NONE

hexchat.hook_print("Focus Tab", on_focus_tab)