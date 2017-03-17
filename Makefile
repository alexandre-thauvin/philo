##
## Makefile for  in /home/aneopsy/PSU_2016_philo/
##
## Made by Paul THEIS
## Login   <theis_p@epitech.eu>
##
## Started on  Mon Mar  6 23:55:28 2017 Paul THEIS
## Last update Mon Mar 13 14:54:18 2017 Paul THEIS
##

DEBUG			?=		no
COLOR			?= 		yes
PARAM			?=		-p 10 -e 1000

VERSION		=		0.1

NAME			=		philo

OBJDIR		=		obj
SRCDIR		=		src
INCLUDE		=		-I include/
SRCDIRS		=		$(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
SRCS			=		main.c
OBJS			=		$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, \
							$(addprefix $(SRCDIR)/, $(SRCS)))

CC				?=		gcc
AR				=		ar
RM				=		rm -Rf
MKDIR			= 	mkdir -p
RMDIR			=		rmdir --ignore-fail-on-non-empty

LVL				?=	3

ifeq ($(DEBUG), yes)
CFLAGS		=		-g -pg -pedantic
else
CFLAGS		=		-Werror -pedantic
endif
CFLAGS	 	+=	-W -Wall -Wextra -O$(LVL)
CFLAGS	+= $(INCLUDE)
LIB				=		libriceferee.so -l pthread
DFLAGS			=	-Y -w80 $(INCLUDE)
LDFLAGS			+=	$(LIB)

GREEN			=		\033[1;32m
YELLOW		=		\033[1;33m
BLUE			=		\033[1;34m
WHITE			=		\033[0m
ifneq ($(COLOR), no)
CFLAGS			+=	-fdiagnostics-color
endif


name			:		buildrepo project_compil

project_compil	:	$(OBJS)
				@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
				@echo "$(GREEN)\n<--->\t ♩♪♫ $(NAME) $(YELLOW)" \
				" Compiled Sucesfully $(WHITE)\n"

all				:		name

clean			:
							$(RM) $(OBJDIR)

fclean		:		clean
							$(RM) $(NAME) $(LIBDIR)

re				:		fclean all

depend		:
							makedepend $(SRC) $(DFLAGS)

val				:
							@make re && valgrind ./$(NAME) $(PARAM)

val+			:
							@make re && valgrind --leak-check=full ./$(NAME) $(PARAM)

exe				:
							export LD_LIBRARY_PATH=$(pwd)
							@make re && LD_PRELOAD=libriceferee.so ./$(NAME) $(PARAM)

.PHONY		:		all clean fclean re %.o %.s

.SUFFIXES	: .o.c .s.c

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
