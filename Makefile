# **************************************************************************** #
#                                   PHILO                                      #
# **************************************************************************** #

# --- Colors ---
GREEN   = \033[1;32m
BLUE    = \033[1;34m
YELLOW  = \033[1;33m
RED     = \033[1;31m
RESET   = \033[0m

# --- Variables ---
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -O3
NAME    = philo

SRCS    = main.c utils.c init.c
OBJS    = $(SRCS:.c=.o)

# --- Default rule ---
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)🔨  Compilation de $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)✅  Build terminé !$(RESET)"

# --- Compilation .c -> .o ---
%.o: %.c
	@echo "$(YELLOW)⚙️  Compilation de $< ...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# --- Clean ---
clean:
	@echo "$(RED)🧹  Suppression des fichiers objets...$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)🗑️  Suppression de l'exécutable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
