# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 15:08:52 by cdomet-d          #+#    #+#              #
#    Updated: 2025/03/03 15:15:54 by cdomet-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= ircserv
BDIR:=.bdir/
SRC_DIR:= src/
H:= headers/

CC:=c++
CFLAGS:= -Werror -Wextra -Wall -Wshadow -g3 -std=c++98
CXXFLAGS:=-MMD -MP -I $(H)
MAKEFLAGS:=--no-print-directory

SRC_PATH+= $(addprefix $(SRC_DIR), $(SRC))
SRC=	Client.cpp \
		Server.cpp \
		main.cpp \
		Client.cpp \
		CommandManager.cpp \
		CommandParam.cpp \
		CommandSpec.cpp \
		InputTokenizer.cpp \
		Join.cpp \
		ParamCheckers.cpp \
		main.cpp \

OBJ:=$(addprefix $(BDIR), $(SRC_PATH:%.cpp=%.o))
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

-include $(DEPS)

clean:
	@echo
	@printf '$(CYBOLD)%.30s\n$(R)' "-- Cleaning... -------------------------------"
	$(RM) $(BDIR)

	
fclean: clean
	$(RM) $(NAME) 
	@echo
	
re: fclean all

info:
	@echo $(CXXFLAGS)
	@echo $(SRC_PATH)
	@echo $(SRC)

.PHONY: all clean info fclean re

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
