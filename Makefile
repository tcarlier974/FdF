NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c \
		utils.c \
		draw.c \
		rgb.c \
		iso.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -I./libft  -g -fsanitize=address -c $< -o $@

$(NAME): $(OBJ) libft.a libmlx.a
	git add .; git commit -m "auto"; git push
	$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -L./libft -lft -framework OpenGL -g -fsanitize=address -framework AppKit -o $(NAME)

all: $(NAME)

libft.a:
	make -C ./libft

libmlx.a :
	make -C ./mlx

clean:
	rm -f $(OBJ)
	make -C ./libft clean
	make -C ./mlx clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re