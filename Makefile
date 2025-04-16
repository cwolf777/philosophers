CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
NAME = philo
SOURCES = main.c utils.c gb_collec.c init.c \
			testing.c routine.c
OBJECTS = $(SOURCES:.c=.o)

all:$(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re