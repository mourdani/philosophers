NAME	= philo

SRC	= src/philo.c \
	  src/utils.c \
		src/free.c \
	  src/routine.c \
	  src/init.c \
	  src/thread.c

OBJ	= ${patsubst src/%, obj/%, $(SRC:.c=.o)}

CC	= cc

CFLAGS	= -Wall -Wextra -Werror -g
#GFLAG = -fsanitize=thread
THREAD = -lpthread
CLEAN_O	= @echo "Object files removed."
CLEAN_A	= @echo "Environemment reset succefully."
DONE	= @echo "Philo is ready to use!"


$(NAME): obj $(OBJ)
	@$(CC) $(CFLAGS) $(THREAD) -o $(NAME) $(OBJ)
	$(DONE)

debug: obj $(OBJ)
	@$(CC) $(CFLAGS) $(GFLAG) $(THREAD) -o $(NAME) $(OBJ)
	$(DONE)

all:	 $(NAME)


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
