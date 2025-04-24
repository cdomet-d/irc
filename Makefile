# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 15:08:52 by cdomet-d          #+#    #+#              #
#    Updated: 2025/04/24 19:10:20 by cdomet-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .make/*.mk

NAME:= ircserv
DEBUG_NAME:= d-ircserv

BOT_NAME:= ircbot
BOT_DEBUG_NAME:= d-ircbot

CC:=c++
CFLAGS:= -std=c++98 -Werror -Wextra -Wall -Wshadow -O1
DEBUG_FLAGS:= -std=c++98 -Wextra -Wall -Wshadow -g3

MAKEFLAGS:=--no-print-directory

VFLAGS:= --leak-check=full --log-file="val.log" --show-leak-kinds=all --track-fds=yes

SERVER_CXXFLAGS:=-MMD -MP $(SERVER_INCLUDES)
BOT_CXXFLAGS:=-MMD -MP $(BOT_INCLUDES)

BUILD:= .build/
BDIR:= $(BUILD)bdir/
DEBUG_BDIR:=$(BUILD)debug_bdir/
BOT_BDIR:=$(BUILD)bot_bdir/
DEBUG_BOT_BDIR:=$(BUILD)debug_bot_bdir/

RM:= rm -rf

# ----------------------------- RULES ---------------------------------------- #

all: $(NAME)

SERVER_OBJ:=$(addprefix $(BDIR), $(SERVER_SRC:%.cpp=%.o))
SERVER_DEPS:=$(SERVER_OBJ:%.o=%.d)

$(NAME): $(SERVER_OBJ)
	@echo
	@printf '$(CYBOLD)%.50s\n\n$(R)' "-- Making $(NAME)... --------------------"
	$(CC) $(SERVER_OBJ) -o $(NAME)
	@echo
	@printf '$(CYBOLD)%.50s\n\n$(R)' "-- $(NAME) done ! -----------------------"

$(BDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(CC) $(CFLAGS) $@"
	@$(CC) $(CFLAGS) $(SERVER_CXXFLAGS) -o $@ -c $<

-include $(SERVER_DEPS)

debug: $(DEBUG_NAME)

DEBUG_OBJ:=$(addprefix $(DEBUG_BDIR), $(SERVER_SRC:%.cpp=%.o))
DEBUG_DEPS:=$(DEBUG_OBJ:%.o=%.d)

$(DEBUG_NAME): $(DEBUG_OBJ)
	@echo
	@printf '$(CYBOLD)%.50s\n\n$(R)' "-- Making $(DEBUG_NAME)... --------------"
	$(CC) $(DEBUG_OBJ) -o $(DEBUG_NAME)
	@echo
	@printf '$(CYBOLD)%.50s\n\n$(R)' "-- $(DEBUG_NAME) done ! -----------------"

$(DEBUG_BDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(CC) $(DEBUG_FLAGS) $@"
	@$(CC) $(DEBUG_FLAGS) $(SERVER_CXXFLAGS) -o $@ -c $<

-include $(DEBUG_DEPS)

bot: $(BOT_NAME)

BOT_OBJ:=$(addprefix $(BOT_BDIR), $(BOT_SRC:%.cpp=%.o))
BDEPS:=$(BOT_OBJ:%.o=%.d)

$(BOT_NAME): $(BOT_OBJ)
	@echo
	@printf '$(CYBOLD)%.50s\n\n$(R)' "-- Making $(BOT_NAME)... ----------------"
	$(CC) $(BOT_OBJ) -o $(BOT_NAME)
	@echo
	@printf '$(CYBOLD)%.50s\n\n$(R)' "-- $(BOT_NAME) done ! -------------------"

$(BOT_BDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(CC) $(CFLAGS) $@"
	@$(CC) $(CFLAGS) $(BOT_CXXFLAGS) -o $@ -c $<

debugbot: $(BOT_DEBUG_NAME)

DEBUG_BOT_OBJ:=$(addprefix $(DEBUG_BOT_BDIR), $(BOT_SRC:%.cpp=%.o))
BDEPS:=$(DEBUG_BOT_OBJ:%.o=%.d)

$(BOT_DEBUG_NAME): $(DEBUG_BOT_OBJ)
	@echo
	@printf '$(CYBOLD)%.50s\n\n$(R)' "-- Making $(BOT_DEBUG_NAME)... ----------------"
	$(CC) $(DEBUG_BOT_OBJ) -o $(BOT_DEBUG_NAME)
	@echo
	@printf '$(CYBOLD)%.50s\n\n$(R)' "-- $(BOT_DEBUG_NAME) done ! -------------------"

$(DEBUG_BOT_BDIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(CC) $(DFLAGS) $@"
	@$(CC) $(DFLAGS) $(BOT_CXXFLAGS) -o $@ -c $<

-include $(BDEPS)

cleanserv:
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Cleaning server & debug server... ---------------------"
	$(RM) $(BDIR)
	$(RM) $(DEBUG_BDIR)
	@echo

fcleanserv: clean
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Removing server & debug server executables... ----------"
	$(RM) $(NAME)
	$(RM) $(DEBUG_NAME)
	@echo
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Removing logs... ----------------"
	$(RM) serv.log
	@echo

reserv: fclean all

cleanbot:
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Cleaning bot & debug bot... ------------------------"
	$(RM) $(BOT_BDIR)
	$(RM) $(DEBUG_BOT_BDIR)
	$(RM) *txt
	@echo

fcleanbot: cleanbot
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Removing bot & debug executables... -------------"
	$(RM) $(BOT_NAME)
	$(RM) $(BOT_DEBUG_NAME)
	@echo
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Removing logs... -------------------"
	$(RM) bot.log
	@echo

rebot: fcleanbot bot

clean:
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Cleaning everything... ------------------------"
	$(RM) $(BUILD)
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Removing logs... ------------------------"
	$(RM) *.txt
	$(RM) *.log
	@echo

fclean: clean
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Removing all executables... -------------"
	$(RM) $(BOT_NAME)
	$(RM) $(BOT_DEBUG_NAME)
	$(RM) $(NAME)
	$(RM) $(DEBUG_NAME)
	@echo
	@echo

re: fclean all bot

run: all
	@if echo $(MAKECMDGOALS) | grep -q "6667"; then \
		./$(NAME) 6667 0; \
	else \
		./$(NAME) 4444 0; \
	fi

drun: debug
	@if echo $(MAKECMDGOALS) | grep -q "6667"; then \
		valgrind $(VFLAGS) ./$(DEBUG_NAME) 6667 0; \
	else \
		valgrind $(VFLAGS) ./$(DEBUG_NAME) 4444 0; \
	fi

dbrun: debugbot
	@if echo $(MAKECMDGOALS) | grep -q "6667"; then \
		valgrind $(VFLAGS) ./$(BOT_DEBUG_NAME) 0.0.0.0 6667 0; \
	else \
		valgrind $(VFLAGS) --trace-children=yes ./$(BOT_DEBUG_NAME) 0.0.0.0 4444 0; \
	fi

brun: bot
	@if echo $(MAKECMDGOALS) | grep -q "6667"; then \
		./$(BOT_NAME) 0.0.0.0 6667 0; \
	else \
		./$(BOT_NAME) 0.0.0.0 4444 0; \
	fi

info:
	@echo $(S_CXXFLAGS)
	@echo
	@echo $(SERVER_SRC)
	@echo
	@echo $(B_CXXFLAGS)
	@echo
	@echo $(BOT_SRC)

track:
	bash .scripts/track-remote-branches.sh


format:
	@printf '$(CYBOLD)%.50s\n$(R)' "-- Formatting... --------------------------"
	bash .scripts/format-all.sh 

.PHONY: all bot debug clean cleanserv cleanbot fclean re info run drun format -list
