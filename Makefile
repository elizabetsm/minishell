NAME = minishell

LIBFT = libft/

FILES = src/main.c

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
	@$(CC) $(FLAGS) $(OBG) -o $(NAME) $(LIBRA)
