NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -Wall -Wextra -Werror -Imlx -c $< -o $@


$(NAME): $(OBJ) libft.a libmlx.a
	$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

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

re: fclean all

.PHONY: all clean fclean re