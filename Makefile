# Makefile for cub3d

# Variables
NAME=cub3d

# Compiler options
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
CLIBS = -L$(LIB_FOLDER) -lft -lm -lreadline
CINCLUDES  = -I$(INCLUDE_FOLDER) 
RM = rm -rf

# Colors
RED    = 	\033[0;31m
GREEN  = 	\033[0;32m
ORANGE = 	\033[0;33m
BLUE   = 	\033[34m
PURPLE = 	\033[35m
RESET  = 	\033[0m

# Folders
INCLUDE_FOLDER = ./includes/
SRC_FOLDER     = ./src/
OBJ_FOLDER     = ./obj/
LIB_FOLDER     = ./lib/

# Files
LIBFT = $(LIB_FOLDER)libft.a
SRCS = $(addprefix $(SRC_FOLDER), 						\
	main.c)

# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJ_FOLDER)%.o)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

# Targets
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME)
	@echo "\n$(ORANGE)╔══════════════════════════╗"
	@echo "$(ORANGE)║    $(GREEN)$(NAME):   created$(ORANGE)      ║"
	@echo "$(ORANGE)╚══════════════════════════╝$(RESET)"

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c 
	@mkdir -p $(@D)
	@echo -n "$(BLUE).$(RESET)"
	@$(CC) $(CFLAGS) $(CINCLUDES)-c $< -o $@

$(LIBFT):
	@echo "$(BLUE)┌───────────────────────┐"
	@echo "│  $(ORANGE)Compiling:  libft.a$(BLUE)  │"
	@echo "$(BLUE)└───────────────────────┘$(RESET)"
	@$(MAKE) -sC $(LIB_FOLDER) DEBUG=$(DEBUG)

clean:
	@$(RM) $(OBJ_FOLDER) readline.supp
	@echo "$(PURPLE)┌───────────────────────┐"
	@echo "│     $(RED)[✓]  CLEANED!$(PURPLE)     │"
	@echo "$(PURPLE)└───────────────────────┘$(RESET)"

fclean: clean
	@make -sC $(LIB_FOLDER) fclean
	@$(RM) $(NAME)

re: fclean all