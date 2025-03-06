# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 15:08:52 by cdomet-d          #+#    #+#              #
#    Updated: 2025/03/06 16:59:41 by cdomet-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= ircserv
DEBUG_NAME:= d-ircserv
BDIR:=.bdir/
DBDIR:=.dbdir/
H:=  -I headers/ \
	-I headers/builder/command-execution/ \
	-I headers/builder/command-validation/ \
	-I headers/builder/manager/ \
	-I headers/client/ \
	-I headers/debug/ \
	-I headers/server/ \

CC:=c++
CFLAGS:= -std=c++98 -Werror -Wextra -Wall -Wshadow
DFLAGS:= -std=c++98 -Wshadow -Wextra -Wall -g3
CXXFLAGS:=-MMD -MP $(H)
MAKEFLAGS:=--no-print-directory

# ----------------------------- SOURCES DIRECTORIES -------------------------- #

SRC_DIR:= src/

BUILDER_DIR:= $(SRC_DIR)builder/
BUILDER_EXEC_DIR:= $(BUILDER_DIR)command-execution/
BUILDER_VALID_DIR:= $(BUILDER_DIR)command-validation/
BUILDER_MANAGE_DIR:= $(BUILDER_DIR)manager/

CLI_DIR:= $(SRC_DIR)client/
DEBUG_DIR:= $(SRC_DIR)debug/
SERV_DIR:= $(SRC_DIR)server/

# ----------------------------- SOURCES FILES -------------------------------- #

SERV_SRC:=				Channel.cpp \
						Server.cpp \
						reply.cpp \

DEBUG_SRC:=				Log.cpp \

CLI_SRC:=				Client.cpp \

BUILDER_EXEC_SRC:=		Privmsg.cpp \
						NickUser.cpp \
						Join.cpp \
						Topic.cpp \

BUILDER_VALID_SRC:=		InputClientParsing.cpp \
						MessageValidator.cpp \

BUILDER_MANAGE_SRC:=	\

SRC_ROOT:=				main.cpp \

# ----------------------------- BUILDING PATH -------------------------------- #

SRC:= $(addprefix $(SRC_DIR), $(SRC_ROOT))
SRC+= $(addprefix $(BUILDER_EXEC_DIR), $(BUILDER_EXEC_SRC))
SRC+= $(addprefix $(BUILDER_MANAGE_DIR), $(BUILDER_MANAGE_SRC))
SRC+= $(addprefix $(BUILDER_VALID_DIR), $(BUILDER_VALID_SRC))
SRC+= $(addprefix $(CLI_DIR), $(CLI_SRC))
SRC+= $(addprefix $(DEBUG_DIR), $(DEBUG_SRC))
SRC+= $(addprefix $(SERV_DIR), $(SERV_SRC))

OBJ:=$(addprefix $(BDIR), $(SRC:%.cpp=%.o))
DEPS:=$(OBJ:%.o=%.d)

RM:= rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- Making $(NAME)... ----------------------"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- $(NAME) done ! --------------------------"

$(BDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$@"
	$(CC) $(CFLAGS) $(CXXFLAGS) -o $@ -c $<

debug: $(DEBUG_NAME)

DOBJ:=$(addprefix $(DBDIR), $(SRC:%.cpp=%.o))
DDEPS:=$(DOBJ:%.o=%.d)

$(DEBUG_NAME): $(DOBJ)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- Making $(DEBUG_NAME)... ----------------------"
	$(CC) $(DFLAGS) $(DOBJ) -o $(DEBUG_NAME)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- $(DEBUG_NAME) done ! --------------------------"

$(DBDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$@"
	$(CC) $(DFLAGS) $(CXXFLAGS) -o $@ -c $<

-include $(DEPS)

clean:
	@echo
	@printf '$(CYBOLD)%.30s\n$(R)' "-- Cleaning... -------------------------------"
	$(RM) $(BDIR)
	$(RM) $(DBDIR)
	$(RM) src.mk


fclean: clean
	$(RM) $(NAME)
	$(RM) $(DEBUG_NAME)
	@echo

re: fclean all

info:
	@echo $(CXXFLAGS)
	@echo
	@echo $(SRC_PATH)
	@echo
	@echo $(SRC)

.PHONY: all clean info fclean re debug

# Formatting combinations
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
