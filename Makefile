CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SOURCES = 	main.c utils.c utils_time.c philo_status.c gb_collec.c init.c \
			philo_routine.c philo_routine2.c waiter_routine.c \
			start_threads.c
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