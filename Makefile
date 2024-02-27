# Makefile for cub3D

# Variables
NAME=cub3D

# Compiler options
CC = cc
CFLAGS =  -g -Wall -Werror -Wextra #-O3 
CLIBS = -L$(LIBFT_FOLDER) -L$(MLX_FOLDER) -lft -lm -lmlx -lX11 -lXext
CINCLUDES  = -I$(INCLUDE_FOLDER) -I$(MLX_FOLDER)
RM = rm -rf

# Colors
RED    = 	\033[0;31m
GREEN  = 	\033[0;32m
ORANGE = 	\033[0;33m
BLUE   = 	\033[34m
PURPLE = 	\033[35m
RESET  = 	\033[0m

# Folders
INCLUDE_FOLDER 	= ./includes/
SRC_FOLDER     	= ./src/
OBJ_FOLDER     	= ./obj/
LIB_FOLDER     	= ./lib/
LIBFT_FOLDER    = $(LIB_FOLDER)libft/
MLX_FOLDER		= $(LIB_FOLDER)minilibx-linux/
MAPS_FOLDER 	= ./maps/

# Files
LIBFT = $(LIBFT_FOLDER)libft.a
MLX = $(MLX_FOLDER)libmlx.a
BANNER = $(LIBFT_FOLDER)make_banner.sh
SRCS = $(addprefix $(SRC_FOLDER), 						\
	parsing/parsing_main.c								\
	parsing/parsing_utils.c								\
	parsing/parsing_utils2.c							\
	parsing/handle_textures.c							\
	parsing/handle_colors.c								\
	parsing/parse_textures_and_colors.c					\
	parsing/parse_map.c									\
	controller/controller.c								\
	core/main.c											\
	core/cub.c											\
	core/math.c											\
	entities/img.c										\
	entities/img_utils.c								\
	entities/map.c										\
	entities/map2d.c									\
	entities/map2d_utils.c								\
	entities/map3d.c									\
	entities/map3d_utils.c								\
	entities/draw_wall.c								\
	entities/player.c									\
	entities/player_utils.c								\
	entities/column.c									\
	model/model.c										\
	view/mlx_win.c										\
	view/view.c											\
	)

# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJ_FOLDER)%.o)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

# Targets
.PHONY: all clean fclean re

all: MSG_START $(NAME) MSG_DONE

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(OBJS) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME)

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c 
	@mkdir -p $(@D)
	@echo -n "$(BLUE).$(RESET)"
	@$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_FOLDER)

$(MLX):
	@$(BANNER) MLX compiling "$(ORANGE)"
	@make --no-print-directory -C > /dev/null 2>&1 $(MLX_FOLDER)
	@$(BANNER) MLX compiled "$(GREEN)"

clean:
	@make --no-print-directory -C $(LIBFT_FOLDER) clean
	@$(RM) $(OBJ_FOLDER)
	@$(BANNER) $(NAME) "removed object files" "$(RED)"

fclean: clean
	@make -sC $(LIBFT_FOLDER) fclean
	@make --no-print-directory -sC $(MLX_FOLDER) clean
	@$(RM) $(NAME)
	@$(BANNER) $(NAME) "removed program" "$(RED)"

re: fclean all

run1: all
	@./$(NAME) $(MAPS_FOLDER)test.cub

run2: all
	@./$(NAME) $(MAPS_FOLDER)creppy.cub

rerun: re run1

val: all
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(MAPS_FOLDER)test.cub

MSG_START:
	@$(BANNER) $(NAME) compiling "$(ORANGE)"

MSG_DONE:
	@$(BANNER) $(NAME) compiled "$(GREEN)"