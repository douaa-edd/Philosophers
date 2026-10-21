NAME = philo
SRCS= initialisation.c main.c routine.c monitor.c utils.c 
OBJS=${SRCS:%.c=%.o}
HEADER = philo.h 
FLAGS=-Wall -Wextra -Werror -pthread
RM=rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS) 


%.o: %.c $(HEADER)
	cc $(FLAGS)  -c $< -o $@
clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all