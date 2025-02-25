PASS : <password>
	-> ex : /pass my_password	

NICK : <nickname> 
	->ex : /nick my_nickname

USER : <username> 0 * <realname> 
	->ex : /user my_username 0 * :My real name

OPER : <user> <password> 
	->ex : /oper my_username my_password

QUIT : [<quit message>] 
	->ex : /quit going to eat. bye !

JOIN : <channel>{,channel} [key{,key}] 
	->ex : /join #channel_name

PART : <channel>{,<channel>} [<reason>] 
	->ex : /part #channel_name Got to go

TOPIC : <channel> [<topic>] 
	->ex : /topic #channel_name Pizza

INVITE : <nickname> <channel>
	-> ex : /invite some_nickname #channel_name

KICK : <channel> <user> *("," <user> ) [<comment>]
	-> ex : /kick #channel_name some_username Badly behaved

PRIVMSG : <receiver>{,<receiver>} <text to be sent>
	-> ex : /msg username_or_channel Hey how are you ?

MODE : <channel> [<modestring> [<mode arguments>...]]
	-> ex : /mode #channel_name [+|-]modes params