NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -Iinclude/

SRCS_DIR = src/
SRCS = main.c 		\
	error_handler.c \
	ft_atol.c		\
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
	./$(NAME)

.PHONY: clean fclean re bonus