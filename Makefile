CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
RM 				= rm -f
HEADERS 		= -I./includes -I./libft
CRITERION		= -lcriterion
LIBS			= -Llibft -lft -lncurses
LIBFT 			= libft/libft.a
NAME			= Minishell

PATH_SRCS		= ./srcs/
RAW_SRCS		= input.c \
				  get_next_line.c \
				  get_next_line_utils.c \
				  error.c \
				  exec.c \
				  builtin_env.c \
				  builtin_cd.c \
				  exec_builtin.c \
				  parse_command.c \
				  env_utils.c \
				  dict_utils.c \
				  globals.c \
				  tokenizer.c \
				  token_eval.c \
				  token_fcts.c

SRCS			= main.c $(addprefix srcs/, $(RAW_SRCS))
OBJS 			= $(SRCS:.c=.o)
NO_MAIN			= $(filter-out main.o,$(OBJS))

TEST			= minishell_test
TEST_RAW_SRCS	= test_helpers.c \
				  env_test.c \
				  inputs_correct.c \
				  tokenizer_tests.c \
				  token_eval_tests.c \
				  tokens_tests.c \
				  utils_tests.c \
				  env_utils_tests.c \
				  exec_builtin_tests.c \
				  exec_tests.c \
				  dict_utils_tests.c 

TEST_SRCS		= $(addprefix tests/,$(TEST_RAW_SRCS))
TEST_OBJS 		= $(TEST_SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all: $(NAME)

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
	@$(MAKE) fclean -C libft

fclean: clean
	$(RM) $(NAME) $(TEST) ${TEST_OBJS} $(LIBFT)

re: fclean all

.PHONY: all clean fclean re test
