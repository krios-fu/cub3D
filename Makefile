GNL= gnl/get_next_line_bonus.c
NAME= cub3dlib.a
SRC= $(GNL) cub3d.c ./srcs/code/utils.c ./srcs/code/check_sprite.c ./srcs/code/check_lines.c ./srcs/code/map_parseo.c ./srcs/code/map_parseo2.c ./srcs/code/sprite.c ./srcs/code/sprite_utils.c ./srcs/code/screenshot.c ./srcs/code/raycasting.c ./srcs/code/raycasting_draw.c ./srcs/code/coordinates.c ./srcs/code/keycode.c ./srcs/code/keymove.c ./srcs/code/error.c
SRC+= 
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)

$(NAME):	$(OBJ)
	@make -sC ./libft/
	@cp libft/libft.a .
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\n\033[36m"****************\\nCompiled...\\n****************\\n"\033[0m\n"

run:
	@clear
	@echo "\n\033[36m"****************\\nStart...\\n****************\\n"\033[0m\n"
	@gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit $(SRC) libft.a -o cub3D
	@rm -rf cub3D.dSYM

all: $(NAME)

clean:
	@rm -f $(NAME) $(OBJ) ./src/code
	@make -sC ./opengl/ clean
	@make -sC ./libft/ fclean
	@clear
	@echo "\n\033[36m"****************\\nDeleted files...\\n****************\\n"\033[0m\n"

fclean: clean
		@rm -rf libft.a
	
re: clean all

.PHONY: all clean re run
