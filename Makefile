##
## Makefile for  in /home/thauvi_a/rendu/tek2/PSU_2016_philo
##
## Made by Alexandre Thauvin
## Login   <thauvi_a@epitech.net>
##
## Started on  Mon Mar  6 10:57:30 2017 Alexandre Thauvin
## Last update Mon Mar  6 11:01:17 2017 Alexandre Thauvin
##

NAME		= philo

SRCS		= main.c

OBJS		= $(SRCS:.c=.o)

GCC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Werror -W -Wextra

LDFLAGS	= libriceferee.so -lpthread


$(NAME): $(OBJS)
	$(GCC) $(OBJS) -o $(NAME) $(LDFLAGS) $(CFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) sources/*~
	$(RM) sources/*#

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:         all clean fclean re
