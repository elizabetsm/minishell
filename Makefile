NAME = minishell

LIBFT = libft/

FILES = src/main.c \
        src/echo.c \
        src/cd.c

LIBRA = libft/libft.a

INC = ./includes/

INC_FILE = $(INC)ft_ls.h

FLAGS = -Wall -Wextra -Werror -I $(INC)

OBG = $(FILES:.c=.o)

CC = gcc

all: $(NAME)

%.o: %.c $(INC_FILE)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBG) $(LIBRA)
	make -C $(LIBFT)
	@$(CC) $(FLAGS) $(OBG) -o $(NAME) $(LIBRA)

clean:
	make clean -C $(LIBFT)
	@rm -f $(OBG)

fclean: clean
	make fclean -C $(LIBFT)
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re