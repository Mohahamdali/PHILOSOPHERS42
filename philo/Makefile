NAME    = philo

SRCS    = main.c initdata.c clean.c monitor_thread.c parsing.c routine_philo.c routine_philo_utils.c initdata_utils.c
OBJS    = $(SRCS:.c=.o)

CC      = cc 
CFLAGS  =  -Wall -Wextra -Werror
RM      = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

