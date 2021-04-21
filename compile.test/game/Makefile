##
## EPITECH PROJECT, 2020
## B-OOP-400-MPL-4-1-arcade-alec.ferrari
## File description:
## Makefile
##

CXX	=	g++

RM	=	rm -f
CPPFLAGS	=	-W -Wall -Wextra -fPIC -Iinclude
LDFLAGS	=	-shared

NAME	=	nibbler_test

SRCS	=	src/GameObject.cpp src/nibbler_game.cpp
OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME):	$(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME).so

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME).so
