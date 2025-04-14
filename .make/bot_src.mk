# ----------------------------- BOT SOURCES DIRECTORIES ---------------------- #
BOT_SRC_DIR:= bot/src/
BOT_HEA_DIR:= bot/headers/

H:=  -I $(SERV_HEA_DIR) \

# ----------------------------- BOT SOURCES FILES ---------------------------- #

SRC_ROOT:=			main.cpp \

# ----------------------------- BOT FILE BUILDING PATH ----------------------- #

B_SRC:= $(addprefix $(BOT_SRC_DIR), $(SRC_ROOT))