# ----------------------------- BOT SOURCES DIRECTORIES ---------------------- #
BOT_SRC_DIR:= bot/src/
BOT_HEA_DIR:= bot/headers/

BOT_INC:= -I $(BOT_HEA_DIR) \

# ----------------------------- BOT SOURCES FILES ---------------------------- #

SRC_ROOT:=	Bot.cpp \
			main.cpp \
			Reply.cpp \
			Message.cpp \
			Cmd.cpp \
			Api.cpp \
			Utils.cpp \

# ----------------------------- BOT FILE BUILDING PATH ----------------------- #

B_SRC:= $(addprefix $(BOT_SRC_DIR), $(SRC_ROOT))