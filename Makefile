_END=\033[0m
_BOLD=\033[1m
_UNDER=\033[4m
_REV=\033[7m

_DEFAULT=\033[39m
_RED=\033[31m
_GREEN=\033[32m
_YELLOW=\033[33m
_BLUE=\033[34m
_MAGENTA=\033[35m
_CYAN=\033[36m
_LIGHTGRAY=\033[37m
_DARKGRAY=\033[90m
_LIGHTRED=\033[91m
_LIGHTGREEN=\033[92m
_LIGHTYELLOW=\033[93m
_LIGHTBLUE=\033[94m
_LIGHTMAGENTA=\033[95m
_LIGHTCYAN=\033[96m
_WHITE=\033[97m

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS += -O3 -fno-builtin
CFLAGS += -fsanitize=address

MAKE = make --no-print-directory

HEADERS = \
	./includes/minishell.h

SRCS_LIB = \
	./lib/ft_atoi.c \
	./lib/ft_itoa.c \
	./lib/ft_bzero.c \
	./lib/ft_nblen.c \
	./lib/ft_is_p1.c \
	./lib/ft_is_p2.c \
	./lib/ft_lstadd_back.c \
	./lib/ft_lstadd_front.c \
	./lib/ft_lstnew.c \
	./lib/ft_lstsize.c \
	./lib/ft_putcolor.c \
	./lib/ft_putstr.c \
	./lib/ft_strchr.c \
	./lib/ft_strcmp.c \
	./lib/ft_strdup.c \
	./lib/ft_strjoin.c \
	./lib/ft_strlen.c \
	./lib/gc_clean.c \
	./lib/gc_free.c \
	./lib/gc_malloc.c \
	./lib/ft_calloc.c \
	./lib/ft_split.c \
	./lib/ft_split_spaces.c \
	./lib/ft_memcpy.c \
	./lib/ft_strcat.c \
	./lib/ft_putchar.c \

SRCS_MS = \
	./src/builtin_cd.c \
	./src/builtin_env.c \
	./src/builtin_pwd.c \
	./src/builtin_echo.c \
	./src/close_handler.c \
	./src/minishell.c \
	./src/exec_test.c \
	./src/process_input.c \
	./src/env.c \
	./src/exec.c \
	./src/replace_env_value.c \
	./src/read_line.c \
	./src/termcap.c \
	./src/termctl.c \

SRCS = $(SRCS_LIB) $(SRCS_MS)

OBJS = $(SRCS:%.c=%.o)

%.o: %.c $(HEADERS) Makefile
	@printf "[ $(_GREEN)$(_BOLD)compiling$(_END) ] $(_BLUE)$(_BOLD)$<$(_END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@printf "[ $(_YELLOW)$(_BOLD)building$(_END) ] $(_BLUE)$(_BOLD)$(NAME)$(_END)\n"
	@$(CC) $(CFLAGS) -ltermcap -o $(NAME) $(OBJS)
	@printf "[ $(_MAGENTA)$(_BOLD)done$(_END) ]\n"

clean:
	@printf "[ $(_RED)$(_BOLD)removing$(_END) ] $(_BLUE)$(_BOLD)objs$(_END)\n"
	@$(RM) $(OBJS)

fclean: clean
	@printf "[ $(_RED)$(_BOLD)removing$(_END) ] $(_BLUE)$(_BOLD)$(NAME)$(_END)\n"
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) all

run: all
	@printf "[ $(_MAGENTA)$(_BOLD)running$(_END) ] $(_BLUE)$(_BOLD)$(NAME)...$(_END)\n"
	@./$(NAME)

norm:
	@norminette

leaks: all
ifneq (,$(findstring fsanitize,$(CFLAGS)))
	@echo "please use without fsanitize"
else
ifeq ($(shell uname -s),Linux)
	@valgrind -s --leak-check=full --show-reachable=yes --track-origins=yes ./$(NAME)
endif
ifeq ($(shell uname -s),Darwin)
	@leaks --atExit -- ./$(NAME)
endif
endif

.PHONY: all clean fclean re run norm leaks