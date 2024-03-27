###########################################################################
#### SOURCES

SRC_FOLDER	= srcs/
SRC_FOLDER_BONUS = srcs/bonus/

SRC_FILES	= main.c init.c threads.c utils.c

SRC_FILES_BONUS = 
BUILD = build/


OBJ_FILES	= $(addprefix $(BUILD),$(SRC_FILES:%.c=%.o))
OBJ_FILES_BONUS = $(addprefix $(SRC_FOLDER_BONUS), $(SRC_FILES_BONUS:%.c=%.o))

###########################################################################
#### ARGUMENTS

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -pthread -g3

INCLUDE	= philo.h
INCLUDE_BONUS = 
INCLUDE_PATH = includes/

RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
RESET	=	\033[0m

###########################################################################
#### RULES

$(NAME): $(OBJ_FILES) $(INCLUDES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@echo "$(MAGENTA)Les fichiers modifiés sont: $?$(RESET)"
	@echo "$(GREEN)Compilation réussie !$(RESET)"

build/%.o: srcs/%.c
	@mkdir -p ${BUILD}
	@echo "$(YELLOW)Compilation de $*$(RESET)"
	@$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I/usr/include -c $< -o $@

all : $(NAME)

clean :
	@rm -rf ${BUILD}
	@#@rm -f *.txt
	@rm -f *.o ${OBJ_FILES_BONUS}
	@echo "$(CYAN) Nettoyage des fichiers intermédiaires $(RESET)"

fclean : clean
	@rm -f ${NAME}
	@echo "$(GREEN) Nettoyage terminé $(RESET)"

bonus : $(OBJ_FILES_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_FILES_BONUS) -o $(NAME)
	@echo "$(MAGENTA)Les fichiers modifiés sont: $?$(RESET)"
	@echo "$(GREEN)Compilation réussie !$(RESET)"

 
re : fclean all

.PHONY : all clean fclean re
