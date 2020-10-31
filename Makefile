NAME = minishell

LIBFT = libft/

FILES = src/main.c \
        src/echo.c \
        src/cd.c \
		src/env.c \
		src/utilities.c \
		src/utilities2.c \
		src/utilities3.c

LIBRA = libft/libft.a

INC = ./includes/

INC_FILE = $(INC)ft_ls.h

FLAGS = -Wall -Wextra -Werror -I $(INC)

OBG = $(FILES:.c=.o)

CC = gcc -g -Wall -Wextra -Werror

all: lib $(NAME)

lib:
	@make -C $(LIBFT)

%.o: %.c $(INC_FILE)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBG)
	@$(CC) $(FLAGS) $(OBG) -o $(NAME) $(LIBRA)

clean:
	make -C $(LIBFT) clean
	@rm -f $(OBG)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
