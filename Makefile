# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 15:03:27 by csweetin          #+#    #+#              #
#    Updated: 2025/01/16 16:34:42 by csweetin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := irc
BUILD_DIR := dir_build/
SRC_DIR := src/
INCLUDES := -I includes

CC := c++
CFLAGS := #-Wall -Wextra #-Werror -std=c++98 -g3
CPPFLAGS := $(INCLUDES) -MMD -MP

SRCS := main.cpp \
		CommandResult.cpp \
		CommandManager.cpp \

OBJS := $(SRCS:%.cpp=$(BUILD_DIR)%.o)
DEPS := $(OBJS:%.o=%.d)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean :
	rm -rf $(OBJS) $(DEPS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re