flags = -Wall -Wextra -Werror
NAME = philo
SAN = -fsanitize=thread 
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

FILES = src/philosophers.c \
		src/check_input.c \
		src/philos_atwork.c \
		src/philos_utils.c \
		src/philos_func_utils.c \
		src/printing_msgs.c \

# B_FILES = pipex_bonus.c \
# 		  exec_cmds_bonus.c \
# 		  check_input.c \
# 		  errors.c \
# 		  path.c \
# 		  pipex_utils.c \
# 		  get_next_line/get_next_line.c \
# 		  get_next_line/get_next_line_utils.c

OBJS = $(FILES:.c=.o)

# B_OBJS = $(B_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@(echo "$(GREEN)Creating The Executable:   $(NAME)$(RESET)" && cc $(SAN) $(OBJS) -o $(NAME))
	
%.o: %.c
	@(echo "$(GREEN)Creating Object File: $@$(RESET)" && cc $(SAN) $(flags) -c $< -o $@) 
	
# bonus: $(B_OBJS) $(LIBFT)
# 	@(echo "$(GREEN)Creating The Executable:   $(NAME)$(RESET)" && cc $(B_OBJS) libft/$(LIBFT) -o $(NAME))

clean:
	@echo "$(RED)Cleaning Object Files for Philosophers$(RESET)"
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(RED)Removing $(NAME)$(RESET)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
