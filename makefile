NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -g

SRCS = main.c cleanup.c philoroutine.c monitor.c utils.c time.c init.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re