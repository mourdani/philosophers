
NAME	= philo

SRC	= src/philo.c\

OBJ	= ${patsubst src/%, obj/%, $(SRC:.c=.o)}

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

CLEAN_O	= @echo "Object files removed."
CLEAN_A	= @echo "Environemment reset succefully."
DONE	= @echo "Philo is ready to use!"

$(NAME): $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	$(DONE)

all:	obj $(NAME) 


obj:
	@mkdir -p obj

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf obj $(OBJ)
	$(CLEAN_O)

fclean: clean
	@rm $(NAME)
	$(CLEAN_A)

re : fclean all

.PHONY : all obj clean fclean re
