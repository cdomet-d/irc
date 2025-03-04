/*

//requirement
password is set

//parsing
only one param
<nickname>

//attributes
command name : NICK
state : done or not
command issuer client object
channel object

//methods
-- checkers --
validNick() -> checks if nickname characters are valid or not \
				(1) if no nickname is given display ERR_NONICKNAMEGIVEN \
				(2) if invalid characters display ERR_ERRONEUSNICKNAME \
				(3)	if nickname is already in use display ERR_NICKNAMEINUSE

-- executors --
setNick() -> sets client nickname to given string \
				send "<old nickname> [ ["!" user] "@"host ]" message \
				to the concerned client	and if in a channel send to all the channel's clients


*/

/*

NICK
:erbium.libera.chat 431 chacham :No nickname given
NICK 0cha
:erbium.libera.chat 432 chacham 0cha :Erroneous Nickname
NICK chacha
:erbium.libera.chat 433 chacham chacha :Nickname is already in use.
NICK chacham
:chacha!~perle@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr NICK :chacham
NICK chacham
//se passe rien

NICK gg
:lol!~rrrrrrrrr@lfbn-lyo-1-144-60.w86-202.abo.wanadoo.fr NICK :gg
:NickServ!NickServ@services.libera.chat NOTICE gg :This nickname is registered. Please choose a different nickname, or identify via /msg NickServ IDENTIFY gurki <password>
//
👉 Le pseudo gg est enregistré auprès de NickServ (le service d'enregistrement des pseudos).
🔹 Si c'est ton pseudo → Tu dois t'identifier avec /msg NickServ IDENTIFY <password>.
🔹 Si ce n'est pas ton pseudo → Tu dois choisir un autre pseudo avec /nick NouveauPseudo.

NICK i
:silver.libera.chat 433 gg i :Nickname is already in use.
//
👉 Le pseudo i est déjà utilisé par quelqu'un d'autre, en ce moment même.
🔹 Ce pseudo peut être enregistré ou non, mais il est déjà pris.
🔹 Tu ne peux pas l'utiliser tant que l'autre utilisateur ne se déconnecte pas.

*/