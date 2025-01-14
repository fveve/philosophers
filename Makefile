NAME = philo

CC = cc

CFLAGS = -g -Wall -Wextra -Werror -I include

HEADER = philo.h

SRCS = main parsing check_args thread_init tools thread_routine thread_utils handle_one_philo

SRC = $(addsuffix .c, $(addprefix src/, $(SRCS)))

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mPHILOSOPHERS Compiled !"
	@$(CC) $(CFLAGS) -lpthread -o $(NAME) $(OBJ)
	@echo "\n\033[0m./philo to execute the program !"

%.o: %.c
	@printf "\033[0;33mGenerating philo objects... %-33.33s\r\n" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "Deleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)

re: fclean all


.PHONY: clean fclean re 