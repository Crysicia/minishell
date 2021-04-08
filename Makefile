CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
RM 				= rm -f
HEADERS 		= -I./includes -I./libft
CRITERION		= -lcriterion
LIBS			= -Llibft -lft
LIBFT 			= libft/libft.a
NAME			= Minishell
PATH_SRCS		= ./srcs/
SRCS			= main.c \
				  srcs/lexer.c \
				  srcs/get_next_line.c \
				  srcs/get_next_line_utils.c \
				  srcs/exec.c \
				  srcs/env.c\
				  srcs/scanner.c\
				  srcs/scanner_discard.c\
				  srcs/scanner_len_fcts.c\
				  srcs/scanner_states.c\
				  srcs/scanner_utils.c

OBJS 			= $(SRCS:.c=.o)
NO_MAIN			= $(filter-out main.o,$(OBJS))
TEST			= minishell_test
TEST_SRCS		= tests/fct_lexer_test.c \
				  tests/env_test.c \
				  tests/scanner_t.c \
				  tests/scanner_states_t.c \
				  tests/utils_tests.c \
				  tests/exec_tests.c

TEST_OBJS 		= $(TEST_SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	@$(MAKE) bonus -C libft

test: $(TEST)
	./$(TEST)
	$(RM) *.test

$(TEST): $(NO_MAIN) $(TEST_OBJS) $(LIBFT)
	$(CC) $(NO_MAIN) $(TEST_OBJS) $(CRITERION) $(LIBS) -o $(TEST)
	$(RM) $(TEST_OBJS)

clean:
	$(RM) $(OBJS)
	@$(MAKE) clean -C libft

fclean: clean
	$(RM) $(NAME) $(TEST) ${TEST_OBJS} $(LIBFT)

re: fclean all

.PHONY: all clean fclean re test
