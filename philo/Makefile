flags = -Wall -Wextra -Werror
NAME = philo
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

FILES = src/philosophers.c \
		src/check_input.c \
		src/philos_atwork.c \
		src/philos_utils.c \
		src/philos_func_utils.c \
		src/printing_msgs.c \

OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@(echo "$(GREEN)Creating The Executable:   $(NAME)$(RESET)" && cc -fsanitize=thread $(OBJS) -o $(NAME))
	
%.o: %.c
	@(echo "$(GREEN)Creating Object File: $@$(RESET)" && cc -g -fsanitize=thread $(flags) -c $< -o $@) 
	
clean:
	@echo "$(RED)Cleaning Object Files for Philosophers$(RESET)"
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(RED)Removing $(NAME)$(RESET)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
