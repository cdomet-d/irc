# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aljulien < aljulien@student.42lyon.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 15:03:27 by csweetin          #+#    #+#              #
#    Updated: 2025/04/15 11:53:44 by aljulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := tester
BUILD_DIR := dir_build/
SRC_DIR := src/
INCLUDES := -I includes

CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98
CPPFLAGS := $(INCLUDES) -MMD -MP

SRCS := main.cpp \
		testers.cpp \

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
	rm outputs/output.txt

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re