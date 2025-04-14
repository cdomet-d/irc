# ----------------------------- SERVER SOURCES DIRECTORIES ------------------- #
SERV_SRC_DIR:= server/src/
SERV_HEA_DIR:= server/headers/

BOT_SRC_DIR:= bot/src/
BOT_HEA_DIR:= bot/headers/

H:=  -I $(SERV_HEA_DIR) \
	-I $(SERV_HEA_DIR)server/ \
	-I $(SERV_HEA_DIR)builder/command-execution/ \
	-I $(SERV_HEA_DIR)builder/command-validation/ \
	-I $(SERV_HEA_DIR)builder/command-validation/checkers/ \
	-I $(SERV_HEA_DIR)builder/manager/ \
	-I $(SERV_HEA_DIR)client/ \
	-I $(SERV_HEA_DIR)debug/ \

BUILD_EXE_DIR:= $(SERV_SRC_DIR)builder/command-execution/
BUILD_VAL_DIR:= $(SERV_SRC_DIR)builder/command-validation/
BUILD_CHECK_DIR:= $(SERV_SRC_DIR)builder/command-validation/checkers/
BUILD_MAN_DIR:= $(SERV_SRC_DIR)builder/manager/

CLI_DIR:= $(SERV_SRC_DIR)client/
DEBUG_DIR:= $(SERV_SRC_DIR)debug/
SERV_DIR:= $(SERV_SRC_DIR)server/


# ----------------------------- SERVER SOURCES FILES ------------------------- #

SERV_SRC:=			Channel.cpp \
					Server.cpp \
					Reply.cpp \

CLI_SRC:=			Client.cpp \
					Message.cpp \
					UserInfo.cpp \

BUILD_EXE_SRC:=		Join.cpp \
					Privmsg.cpp \
					Topic.cpp \
					Part.cpp \
					Mode.cpp \
					Invite.cpp \
					Kick.cpp \
					Who.cpp \
					Pass.cpp \
					Ping.cpp \
					Nick.cpp \
					User.cpp \
					Quit.cpp \

BUILD_VAL_SRC:=		buffer_manip.cpp \
					CmdManager.cpp \
					CmdParam.cpp  \
					CmdSpec.cpp  \

BUILD_CHECK_SRC:=	check_mode.cpp \
					check_registration.cpp \
					check_nick.cpp \
					check_join.cpp \
					check.cpp \
					check_chans.cpp \
					check_mess.cpp \
					extended_checkers.cpp \

BUILD_MAN_SRC:=	\

DEBUG_SRC:=			printers.cpp \

SRC_ROOT:=			main.cpp \

# ----------------------------- SERVER FILE BUILDING PATH -------------------- #

S_SRC:= $(addprefix $(SERV_SRC_DIR), $(SRC_ROOT))
S_SRC+= $(addprefix $(BUILD_EXE_DIR), $(BUILD_EXE_SRC))
S_SRC+= $(addprefix $(BUILD_MAN_DIR), $(BUILD_MAN_SRC))
S_SRC+= $(addprefix $(BUILD_VAL_DIR), $(BUILD_VAL_SRC))
S_SRC+= $(addprefix $(BUILD_CHECK_DIR), $(BUILD_CHECK_SRC))
S_SRC+= $(addprefix $(CLI_DIR), $(CLI_SRC))
S_SRC+= $(addprefix $(DEBUG_DIR), $(DEBUG_SRC))
S_SRC+= $(addprefix $(SERV_DIR), $(SERV_SRC))