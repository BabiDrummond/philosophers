NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -Iinclude/

SRCS_DIR = src/
SRCS = 	action.c 	 \
		destroy.c	 \
		init.c		 \
		main.c 	 	 \
		monitor.c	 \
		simulation.c \
		utils.c
OBJS_DIR = objs/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "\033[0;32mGenerated philo\033[0m"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[95mCompiling \033[0m$(notdir $<)"

clean:
	@echo "\033[0;34mCleaning philo objects\033[0m"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "\033[0;34mCleaning philo\033[0m"
	@rm -f $(NAME)

re: fclean all

run: re
	./$(NAME) 2 200 100 100

valgrind: re
	valgrind --tool=helgrind ./$(NAME) 5 810 500 200

.PHONY: clean fclean re bonus