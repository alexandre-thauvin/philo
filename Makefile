##
## Makefile for  in /home/thauvi_a/rendu/tek2/trade
##
## Made by Alexandre Thauvin
## Login   <thauvi_a@epitech.net>
##
## Started on  Mon Feb 27 11:44:29 2017 Alexandre Thauvin
## Last update Mon Mar  6 10:29:09 2017 Alexandre Thauvin
##

NAME		= trade

SRCS		=

OBJS		= $(SRCS:.c=.o)

GCC		= gcc

RM		= rm -rf

CXXFLAGS	= -Wall -Werror -W -Wextra


$(NAME): $(OBJS)
	$(GCC) $(OBJS) -o $(NAME) $(CXXFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) sources/*~
	$(RM) sources/*#

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:         all clean fclean re
