# -*- coding: UTF-8 -*-
#allTest.py

import hexchat

__module_name__ = "Test Suite"
__module_version__ = "1.0"
__module_description__ = "Combined IRC tests"

hooks = []  # Stores all hook IDs
scripts = [
    "nickIllegalChar.py",
	"nickAlreadyUsed.py",
	"nickNotGiven.py",
	"user.py",
	"join.py"
]

def load_tests():
	hexchat.prnt("All tests reloaded")
	global hooks
	original_hooks = set(dir(hexchat))  # Get pre-existing hooks
    
	for script in scripts:
		try:
			with open(f"/home/aljulien/.config/hexchat/addons/{script}") as f:
				exec(f.read(), globals())
		except Exception as e:
			hexchat.prnt(f"\00307Failed to load {script}: {str(e)}")
    
	# Capture ALL new hooks added by any script
	current_hooks = set(dir(hexchat))
	hooks = list(current_hooks - original_hooks)

def unload(userdata):
	for hook in hooks:
		hexchat.unhook(hook)
	hexchat.prnt("All tests unloaded")

hexchat.hook_unload(unload)
load_tests()
