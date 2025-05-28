NAME    = philo_bonus

SRCS    = main_bonus.c parsing_bonus.c  init_data_bonus.c routine_philo_bonus.c clean_bonus.c routine_two_bonus.c
OBJS    = $(SRCS:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

