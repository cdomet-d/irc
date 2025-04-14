# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 15:08:52 by cdomet-d          #+#    #+#              #
#    Updated: 2025/04/14 15:40:26 by cdomet-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .make/*.mk

NAME:= ircserv
DEBUG_NAME:= d-ircserv
BOT_NAME:= ircbot

CC:=c++
CFLAGS:= -std=c++98 -Werror -Wextra -Wall -Wshadow
DFLAGS:= -std=c++98 -Wextra -Wall -Wshadow -g3
MAKEFLAGS:=--no-print-directory
VFLAGS:= --leak-check=full --log-file="val.log" --show-leak-kinds=all --track-fds=yes

BUILD:= .build/
BDIR:= $(BUILD)bdir/
DBDIR:=$(BUILD)dbdir/
BOT_BDIR:=$(BUILD)bot_bdir/

RM:= rm -rf

# ----------------------------- RULES ---------------------------------------- #

all: $(NAME)

S_CXXFLAGS:=-MMD -MP $(SERV_INC)

OBJ:=$(addprefix $(BDIR), $(S_SRC:%.cpp=%.o))
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
	@$(CC) $(CFLAGS) $(S_CXXFLAGS) -o $@ -c $<

-include $(DEPS)

bot: $(BOT_NAME)

B_CXXFLAGS:=-MMD -MP $(BOT_INC)

BOBJ:=$(addprefix $(BOT_BDIR), $(B_SRC:%.cpp=%.o))
BDEPS:=$(BOBJ:%.o=%.d)

$(BOT_NAME): $(BOBJ)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- Making $(BOT_NAME)... ----------------"
	$(CC) $(BOBJ) -o $(BOT_NAME)
	@echo
	@printf '$(CYBOLD)%.30s\n\n$(R)' "-- $(BOT_NAME) done ! -----------------------"

$(BOT_BDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(CC) $(CFLAGS) $@"
	@$(CC) $(CFLAGS) $(B_CXXFLAGS) -o $@ -c $<

-include $(BDEPS)

debug: $(DEBUG_NAME)

DOBJ:=$(addprefix $(DBDIR), $(S_SRC:%.cpp=%.o))
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
	@$(CC) $(DFLAGS) $(S_CXXFLAGS) -o $@ -c $<

-include $(DDEPS)

clean:
	@echo
	@printf '$(CYBOLD)%.30s\n$(R)' "-- Cleaning... ----------------------------"
	$(RM) $(BUILD)
	$(RM) src.mk
	@echo

cleanserv:
	@echo
	@printf '$(CYBOLD)%.30s\n$(R)' "-- Cleaning... ----------------------------"
	$(RM) $(BDIR)
	$(RM) src.mk
	@echo

cleandebug:
	@echo
	@printf '$(CYBOLD)%.30s\n$(R)' "-- Cleaning debug... ----------------------"
	$(RM) $(DBDIR)
	$(RM) src.mk
	@echo

cleanbot:
	@echo
	@printf '$(CYBOLD)%.30s\n$(R)' "-- Cleaning debug... ----------------------"
	$(RM) $(BOT_BDIR)
	$(RM) src.mk
	@echo

fclean: clean
	@printf '$(CYBOLD)%.30s\n$(R)' "-- Removing excecutables... ---------------"
	$(RM) $(BOT_NAME)
	$(RM) $(DEBUG_NAME)
	$(RM) $(NAME)
	@echo

	@printf '$(CYBOLD)%.30s\n$(R)' "-- Removing logs... -----------------------"
	$(RM) raw.log
	$(RM) val.log
	@echo

re: fclean all

redebug: fclean debug

rebot: fclean bot

info:
	@echo $(S_CXXFLAGS)
	@echo
	@echo $(S_SRC)
	@echo
	@echo $(B_CXXFLAGS)
	@echo
	@echo $(B_SRC)

track:
	bash .scripts/track-remote-branches.sh

run: all
	$(RM) raw.log
	@if echo $(MAKECMDGOALS) | grep -q "6667"; then \
		./$(NAME) 6667 0; \
	else \
		./$(NAME) 4444 0; \
	fi

drun: debug
	$(RM) raw.log
	valgrind $(VFLAGS) ./$(DEBUG_NAME) 4444 0

format:
	@printf '$(CYBOLD)%.30s\n$(R)' "-- Formatting... --------------------------"
	bash .scripts/format-all.sh 

.PHONY: all bot debug clean cleanserv cleandebug cleanbot fclean re redebug info run drun format -list
