NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -Iinclude/

SRCS_DIR = src/
SRCS = main.c 		\
	clean_all.c 	\
	init_data.c		\
	safe_atoi.c		\
	simulation.c	\
	throw_error.c 	\
	validate_input.c
OBJS_DIR = objs/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo -n "\033[0;32mGenerated philo\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[95mCompiling $(notdir $<)"

clean:
	@echo "\033[0;34mCleaning philo objects"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "\033[0;34mCleaning philo"
	@rm -f $(NAME)

re: fclean all

run: re
	./$(NAME) 9 200 100

valgrind: re
	valgrind ./$(NAME) 9 200 100 100

.PHONY: clean fclean re bonus