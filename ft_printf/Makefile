NAME = printf.a
CFLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c \
		ft_printfengine.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all