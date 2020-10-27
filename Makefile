NAME = minishell

LIBFT = libft/

FILES = src/main.c \
        src/echo.c \
        src/cd.c \
		src/env.c \
		src/utilities.c

LIBRA = libft/libft.a

INC = ./includes/

INC_FILE = $(INC)ft_ls.h

FLAGS = -Wall -Wextra -Werror -I $(INC)

OBG = $(FILES:.c=.o)

CC = gcc -g

all: $(NAME)

%.o: %.c $(INC_FILE)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBG)
	make -C $(LIBFT)
	@$(CC) $(FLAGS) $(OBG) -o $(NAME) $(LIBRA)

clean:
	make -C $(LIBFT) clean
	@rm -f $(OBG)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
