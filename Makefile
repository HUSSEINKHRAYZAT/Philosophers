# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = initmain.c mainutilites.c mutexes.c philosophers.c utilites.c philosopherutilites.c
OBJS = $(SRCS:.c=.o)
NAME = philo

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
