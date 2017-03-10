##
## Makefile for  in /home/aneopsy/PSU_2016_philo/
##
## Made by Paul THEIS
## Login   <theis_p@epitech.eu>
##
## Started on  Mon Mar  6 23:55:28 2017 Paul THEIS
## Last update Thu Mar  9 22:12:56 2017 Paul THEIS
##

DEBUG			=		yes

VERSION		=		0.1

NAME			=		philo

SRCS			=		main.c \
							action.c

CC				=		gcc
AR				=		ar
RM				=		rm -Rf

ifeq ($(DEBUG), yes)
CFLAGS		=		-W -Wall -Wextra -g -pg -pedantic
else
CFLAGS		=		-W -Wall -Wextra -Werror -pedantic
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
							@make re && valgrind ./$(NAME) -p 10 -e 1000

val+			:
							@make re && valgrind --leak-check=full ./$(NAME) -p 10 -e 1000

exe				:
							export LD_LIBRARY_PATH=$(pwd)
							@make re && LD_PRELOAD=libriceferee.so ./$(NAME) -p 10 -e 1000

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
