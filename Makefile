# Makefile for cub3D

# Variables
NAME=cub3D

# Compiler options
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
CLIBS = -L$(LIB_FOLDER) -L$(MLX_FOLDER) -lft -lm -lmlx -lX11 -lXext
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
MLX_FOLDER		= ./mlx/
MAPS_FOLDER 	= ./maps/

# Files
LIBFT = $(LIB_FOLDER)libft.a
MLX = $(MLX_FOLDER)libmlx.a
SRCS = $(addprefix $(SRC_FOLDER), 						\
	main.c												\
	cub.c												\
	mlx_main.c											\
	parsing/parsing_main.c								\
	parsing/parsing_utils.c								\
	parsing/parsing_utils2.c							\
	parsing/handle_textures.c							\
	parsing/handle_colors.c								\
	parsing/parse_textures_and_colors.c					\
	parsing/parse_map.c									\
	controller.c										\
	view.c												\
	model.c												\
	img.c												\
	controller/controller.c								\
	core/main.c											\
	core/cub.c											\
	core/dbg.c											\
	core/math.c											\
	entities/img.c										\
	entities/map.c										\
	entities/map2d.c									\
	entities/minimap.c									\
	entities/player.c									\
	entities/column.c									\
	model/model.c										\
	model/collision_check.c								\
	parser/parser.c										\
	raycasting/dda.c									\
	raycasting/map3d.c									\
	view/mlx_win.c										\
	view/view.c											\
	)

# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJ_FOLDER)%.o)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

# Targets
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@./make_banner.sh $(NAME) compiling "$(ORANGE)"
	@$(CC) $(OBJS) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME)
	@./make_banner.sh $(NAME) done "$(GREEN)"

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c 
	@mkdir -p $(@D)
	@echo -n "$(BLUE).$(RESET)"
	@$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(LIBFT):
	@./make_banner.sh libft.a compiling "$(ORANGE)"
	@$(MAKE) -sC $(LIB_FOLDER) DEBUG=$(DEBUG)

$(MLX):
	@./make_banner.sh mlx.a compiling "$(BLUE)"
	@make --no-print-directory -C > /dev/null 2>&1 $(MLX_FOLDER)
	@./make_banner.sh mlx.a created "$(GREEN)"

clean:
	@$(RM) $(OBJ_FOLDER)
	@./make_banner.sh $(NAME) cleaned "$(RED)"

fclean: clean
	@make -sC $(LIB_FOLDER) fclean
	@make -sC $(MLX_FOLDER) clean
	@$(RM) $(NAME)

re: fclean all

run: all
	@./$(NAME) $(MAPS_FOLDER)test.cub

rerun: re run
val: all
	@valgrind ./$(NAME) $(MAPS_FOLDER)test.cub