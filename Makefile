_END=\033[0m
_BOLD=\033[1m
_UNDER=\033[4m
_REV=\033[7m

_RED=\033[31m
_GREEN=\033[32m
_YELLOW=\033[33m
_BLUE=\033[34m
_PURPLE=\033[35m
_CYAN=\033[36m
_WHITE=\033[37m

_IGREY=\033[40m
_IRED=\033[41m
_IGREEN=\033[42m
_IYELLOW=\033[43m
_IBLUE=\033[44m
_IPURPLE=\033[45m
_ICYAN=\033[46m
_IWHITE=\033[47m

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS += -O3 -fno-builtin
# CFLAGS += -fsanitize=address

MAKE = make --no-print-directory

HEADERS = \
	./includes/minishell.h

OBJS = $(SRCS:%.c=%.o)
SRCS = \
	./src/minishell.c

%.o: %.c $(HEADERS)
	@printf "[ $(_GREEN)$(_BOLD)compiling$(_END) ] $(_BLUE)$(_BOLD)$<$(_END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@printf "[ $(_GREEN)$(_BOLD)building$(_END) ] $(_BLUE)$(_BOLD)$(NAME)$(_END)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@printf "[ $(_BLUE)$(_BOLD)done$(_END) ]\n"

clean:
	@printf "[ $(_RED)$(_BOLD)removing$(_END) ] $(_BLUE)$(_BOLD)objs $(_END)\n"
	@$(RM) $(OBJS)

fclean: clean
	@printf "[ $(_RED)$(_BOLD)removing$(_END) ] $(_BLUE)$(_BOLD)$(NAME) $(_END)\n"
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) all

test: all
	@./$(NAME)

norm:
	norminette

.PHONY: all clean fclean re test norm