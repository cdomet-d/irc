# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 15:08:52 by cdomet-d          #+#    #+#              #
#    Updated: 2025/04/01 08:34:05 by aljulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= ircserv
DEBUG_NAME:= d-ircserv

H:=  -I headers/ \
	-I headers/server/ \
	-I headers/builder/command-execution/ \
	-I headers/builder/command-validation/ \
	-I headers/builder/command-validation/checkers/ \
	-I headers/builder/manager/ \
	-I headers/client/ \
	-I headers/debug/ \

CC:=c++
CFLAGS:= -std=c++98 -Werror -Wextra -Wall -Wshadow
DFLAGS:= -std=c++98 -Wextra -Wall -Wshadow -g3
CXXFLAGS:=-MMD -MP $(H)
MAKEFLAGS:=--no-print-directory

# ----------------------------- SOURCES DIRECTORIES -------------------------- #
BDIR:=.bdir/
DBDIR:=.dbdir/

SRC_DIR:= src/

BUILD_EXE_DIR:= $(SRC_DIR)builder/command-execution/
BUILD_VAL_DIR:= $(SRC_DIR)builder/command-validation/
BUILD_CHECK_DIR:= $(SRC_DIR)builder/command-validation/checkers/
BUILD_MAN_DIR:= $(SRC_DIR)builder/manager/

CLI_DIR:= $(SRC_DIR)client/
DEBUG_DIR:= $(SRC_DIR)debug/
SERV_DIR:= $(SRC_DIR)server/

# ----------------------------- SOURCES FILES -------------------------------- #

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

BUILD_MAN_SRC:=	\

DEBUG_SRC:=			printers.cpp \

SRC_ROOT:=			main.cpp \

# ----------------------------- BUILDING PATH -------------------------------- #

SRC:= $(addprefix $(SRC_DIR), $(SRC_ROOT))
SRC+= $(addprefix $(BUILD_EXE_DIR), $(BUILD_EXE_SRC))
SRC+= $(addprefix $(BUILD_MAN_DIR), $(BUILD_MAN_SRC))
SRC+= $(addprefix $(BUILD_VAL_DIR), $(BUILD_VAL_SRC))
SRC+= $(addprefix $(BUILD_CHECK_DIR), $(BUILD_CHECK_SRC))
SRC+= $(addprefix $(CLI_DIR), $(CLI_SRC))
SRC+= $(addprefix $(DEBUG_DIR), $(DEBUG_SRC))
SRC+= $(addprefix $(SERV_DIR), $(SERV_SRC))

# ----------------------------- MAKE ----------------------------------------- #

all: $(NAME)

OBJ:=$(addprefix $(BDIR), $(SRC:%.cpp=%.o))
DEPS:=$(OBJ:%.o=%.d)

$(NAME): $(OBJ)
	$(RM) raw.log
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- Making $(NAME)... --------------------"
	$(CC) $(OBJ) -o $(NAME)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- $(NAME) done ! -----------------------"

$(BDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(CC) $(CFLAGS) $@"
	@$(CC) $(CFLAGS) $(CXXFLAGS) -o $@ -c $<

-include $(DEPS)


# ----------------------------- MAKE DEBUG ----------------------------------- #

debug: $(DEBUG_NAME)

DOBJ:=$(addprefix $(DBDIR), $(SRC:%.cpp=%.o))
DDEPS:=$(DOBJ:%.o=%.d)

$(DEBUG_NAME): $(DOBJ)
	$(RM) raw.log
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- Making $(DEBUG_NAME)... --------------"
	$(CC) $(DFLAGS) $(DOBJ) -o $(DEBUG_NAME)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- $(DEBUG_NAME) done ! -----------------"

$(DBDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(CC) $(DFLAGS) $@"
	@$(CC) $(DFLAGS) $(CXXFLAGS) -o $@ -c $<

-include $(DDEPS)

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
	$(RM) raw.log
	$(RM) $(NAME)
	$(RM) $(DEBUG_NAME)
	@echo

# ----------------------------- MAKE RE -------------------------------------- #

re: fclean all
redebug: fclean debug

# ----------------------------- MAKE INFO ------------------------------------ #

info:
	@echo $(CXXFLAGS)
	@echo
	@echo $(SRC)

# ----------------------------- RUN ------------------------------------------ #

run: all
	./$(NAME) 4444 0

VFLAGS:= --leak-check=full --show-leak-kinds=all --track-fds=yes
drun: debug
	valgrind $(VFLAGS) ./$(DEBUG_NAME) 4444 0



# ----------------------------- FORMAT ------------------------------------------ #

# ---------------------------------------------------------------------------- #

.PHONY: all clean info fclean re debug redebug run drun

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
