NAME = philo_three
SRCS = ft_get_time.c ft_main.c ft_utils.c main_process.c philo3.c
OBJS = $(SRCS:.c=.o)
CC = gcc -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -pthread -o $(NAME)

$(OBJS): %.o : %.c
	$(CC) -c $< -o $@

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS) $(NAME)

re: fclean all

.PHONY: all, re, clean, fclean
