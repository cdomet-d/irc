# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 15:08:52 by cdomet-d          #+#    #+#              #
#    Updated: 2025/03/10 11:00:40 by aljulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= ircserv
DEBUG_NAME:= d-ircserv

H:=  -I headers/ \
	-I headers/server/ \
	-I headers/builder/command-execution/ \
	-I headers/builder/command-validation/ \
	-I headers/builder/manager/ \
	-I headers/client/ \
	-I headers/debug/ \

CC:=c++
CFLAGS:= -std=c++98 -Werror -Wextra -Wall -Wshadow
DFLAGS:= -std=c++98 -Wshadow -g3
CXXFLAGS:=-MMD -MP $(H)
MAKEFLAGS:=--no-print-directory

# ----------------------------- SOURCES DIRECTORIES -------------------------- #
BDIR:=.bdir/
DBDIR:=.dbdir/

SRC_DIR:= src/

BUILD_EXE_DIR:= $(SRC_DIR)builder/command-execution/
BUILD_VAL_DIR:= $(SRC_DIR)builder/command-validation/
BUILD_MAN_DIR:= $(SRC_DIR)builder/manager/

CLI_DIR:= $(SRC_DIR)client/
DEBUG_DIR:= $(SRC_DIR)debug/
SERV_DIR:= $(SRC_DIR)server/

# ----------------------------- SOURCES FILES -------------------------------- #

SERV_SRC:=				Channel.cpp \
						Server.cpp \
						reply.cpp \

DEBUG_SRC:=				Log.cpp \

CLI_SRC:=				Client.cpp \

BUILD_EXE_SRC:=			Join.cpp \
						NickUser.cpp \
						Privmsg.cpp \
						Topic.cpp \
						Part.cpp \
						Mode.cpp \

BUILD_VAL_SRC:=			InputClientParsing.cpp \

BUILD_MAN_SRC:=	\

SRC_ROOT:=				main.cpp \

# ----------------------------- BUILDING PATH -------------------------------- #

SRC:= $(addprefix $(SRC_DIR), $(SRC_ROOT))
SRC+= $(addprefix $(BUILD_EXE_DIR), $(BUILD_EXE_SRC))
SRC+= $(addprefix $(BUILD_MAN_DIR), $(BUILD_MAN_SRC))
SRC+= $(addprefix $(BUILD_VAL_DIR), $(BUILD_VAL_SRC))
SRC+= $(addprefix $(CLI_DIR), $(CLI_SRC))
SRC+= $(addprefix $(DEBUG_DIR), $(DEBUG_SRC))
SRC+= $(addprefix $(SERV_DIR), $(SERV_SRC))

# ----------------------------- MAKE ----------------------------------------- #

all: $(NAME)

OBJ:=$(addprefix $(BDIR), $(SRC:%.cpp=%.o))
DEPS:=$(OBJ:%.o=%.d)

$(NAME): $(OBJ)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- Making $(NAME)... --------------------"
	$(CC) $(OBJ) -o $(NAME)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- $(NAME) done ! -----------------------"

$(BDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(CC) $(CFLAGS) $@"
	@$(CC) $(CFLAGS) $(CXXFLAGS) -o $@ -c $<

# ----------------------------- MAKE DEBUG ----------------------------------- #

debug: $(DEBUG_NAME)

DOBJ:=$(addprefix $(DBDIR), $(SRC:%.cpp=%.o))
DDEPS:=$(DOBJ:%.o=%.d)

$(DEBUG_NAME): $(DOBJ)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- Making $(DEBUG_NAME)... --------------"
	$(CC) $(DFLAGS) $(DOBJ) -o $(DEBUG_NAME)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- $(DEBUG_NAME) done ! -----------------"

$(DBDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(CC) $(DFLAGS) $@"
	@$(CC) $(DFLAGS) $(CXXFLAGS) -o $@ -c $<

-include $(DEPS)

RM:= rm -rf

# ----------------------------- MAKE CLEAN  ---------------------------------- #

clean:
	@echo
	@printf '$(CYBOLD)%.30s\n$(R)' "-- Cleaning... ----------------------------"
	$(RM) $(BDIR)
	$(RM) $(DBDIR)
	$(RM) src.mk

# ----------------------------- MAKE FCLEAN  --------------------------------- #

fclean: clean
	$(RM) $(NAME)
	$(RM) $(DEBUG_NAME)
	@echo

# ----------------------------- MAKE RE -------------------------------------- #

re: fclean all

# ----------------------------- MAKE INFO ------------------------------------ #

info:
	@echo $(CXXFLAGS)
	@echo
	@echo $(SRC_PATH)
	@echo
	@echo $(SRC)

.PHONY: all clean info fclean re debug

# ----------------------------- FORMATTING ----------------------------------- #

PIBOLD= $(BO)$(M)
BLBOLD= $(BO)$(B)
CYBOLD= $(BO)$(C)
PIBOLD= $(BO)$(P)

# Text
# reset
R=\033[0m
# faint
F=\033[2m
# underlined
U=\033[4m
# bold
BO=\033[1m

# Font color
# red
RE=\033[0;31m
# green
G=\033[0;32m
# yellow
Y=\033[0;33m
# blue
B=\033[0;34m
# magenta
M=\033[0;35m
# cyan
C=\033[0;36m
# white
W=\033[0;37m
# pink
P=\033[38;5;206m.

# Background
BG_RED=\033[41m
BG_GREEN=\033[42m
BG_YELLOW=\033[43m
BG_B=\033[44m
BG_MAGENTA=\033[45m
BG_C=\033[46m
BG_WHITE=\033[47m
