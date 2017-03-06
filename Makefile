##
## Makefile for  in /home/thauvi_a/rendu/tek2/PSU_2016_philo
##
## Made by Alexandre Thauvin
## Login   <thauvi_a@epitech.net>
##
## Started on  Mon Mar  6 10:57:30 2017 Alexandre Thauvin
## Last update Mon Mar  6 23:35:17 2017 Paul THEIS
##

DEBUG			=		yes

VERSION		=		0.1

NAME			=		philo

SRCS			=		main.c

CC				=		gcc
AR				=		ar
RM				=		rm -Rf

ifeq ($(DEBUG), yes)
CFLAGS		=		-W -Wall -Wextra -g -pg
else
CFLAGS		=		-W -Wall -Wextra -Werror
endif
CFLAGS	 	+=	-I./include
LIB				=		libriceferee.so -lpthread

GREEN			=		\033[1;32m
YELLOW		=		\033[1;33m
BLUE			=		\033[1;34m
WHITE			=		\033[0m

OBJDIR		=		obj
SRCDIR		=		src
SRCDIRS		=		$(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
OBJS			=		$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, \
							$(addprefix $(SRCDIR)/, $(SRCS)))

name			:		buildrepo project_compil

project_compil	:	$(OBJS)
				@$(CC) $(OBJS) $(LIB) -o $(NAME) $(LDFLAGS)
				@echo "$(GREEN)\n<--->\t ♩♪♫ $(NAME) $(YELLOW)" \
				" Compiled Sucesfully $(WHITE)\n"

all				:		name

clean			:
							$(RM) $(OBJDIR)

fclean		:		clean
							$(RM) $(NAME) $(LIBDIR)

re				:		fclean all

val				:
							@make re && valgrind ./$(NAME)

val+			:
							@make re && valgrind --leak-check=full ./$(NAME)

exe				:
							@make re && LD_PRELOAD=libriceferee.so ./$(NAME) -p 7 -e 15

.PHONY		:		all clean fclean re

$(OBJDIR)/%.o	: 	$(SRCDIR)/%.c
				@$(CC) -c $< -o $@ $(CFLAGS)
				@echo "$(BLUE)<SRC> \t [√] $<\t$(WHITE)"

$(OBJDIR)/$(BASICDIR)/%.o: $(BASICDIR)/%.c
				@$(CC) -c $< -o $@ $(CFLAGS)
				@echo "$(YELLOW)<LIB> \t [√] $<\t$(WHITE)"

buildrepo	:
							@$(call make-repo)
							@echo "$(GREEN)\n<--->\t ♩♪♫ $(NAME) $(YELLOW)" \
							" Repository Init $(WHITE)\n"
print-%		:
							@echo '$*=$($*)'

define make-repo
				for dir in $(SRCDIRS); \
				do \
				mkdir -p $(OBJDIR)/$$dir; \
					done
endef
