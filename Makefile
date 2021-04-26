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

SRCS_LIB = \
	./lib/ft_gnl.c \
	./lib/ft_lstadd_back.c \
	./lib/ft_lstadd_front.c \
	./lib/ft_lstnew.c \
	./lib/ft_putcolor.c \
	./lib/ft_putstr.c \
	./lib/ft_strcmp.c \
	./lib/ft_strdup.c \
	./lib/ft_strjoinc.c \
	./lib/ft_strlen.c \
	./lib/gc_clean.c \
	./lib/gc_free.c \
	./lib/gc_malloc.c \

SRCS_MS = \
	./src/builtin_cd.c \
	./src/catch_signals.c \
	./src/close_handler.c \
	./src/minishell.c \
	./src/exec_test.c \
	./src/process_input.c \

SRCS = $(SRCS_LIB) $(SRCS_MS)

OBJS = $(SRCS:%.c=%.o)

%.o: %.c $(HEADERS) Makefile
	@printf "[ $(_GREEN)$(_BOLD)compiling$(_END) ] $(_BLUE)$(_BOLD)$<$(_END)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@printf "[ $(_YELLOW)$(_BOLD)building$(_END) ] $(_BLUE)$(_BOLD)$(NAME)$(_END)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@printf "[ $(_PURPLE)$(_BOLD)done$(_END) ]\n"

clean:
	@printf "[ $(_RED)$(_BOLD)removing$(_END) ] $(_BLUE)$(_BOLD)objs$(_END)\n"
	@$(RM) $(OBJS)

fclean: clean
	@printf "[ $(_RED)$(_BOLD)removing$(_END) ] $(_BLUE)$(_BOLD)$(NAME)$(_END)\n"
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) all

run: all
	@printf "[ $(_PURPLE)$(_BOLD)running$(_END) ] $(_BLUE)$(_BOLD)$(NAME)...$(_END)\n"
	@./$(NAME)

norm:
	@norminette

valgrind: all
ifneq (,$(findstring fsanitize,$(CFLAGS)))
	@echo "please use without fsanitize"
else
	@valgrind -s --leak-check=full --show-reachable=yes ./$(NAME)
endif

.PHONY: all clean fclean re run norm valgrind