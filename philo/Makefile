CC = cc
FLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=thread
NAME = philo
SRC = philo.c parsing.c help_function.c initialization.c routine.c routine_healpers.c\
		routine_utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
