SHELL			= /bin/sh
.SUFFIXES:
.SUFFIXES:		.c .o .a
CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
RM 				= rm -f
HEADERS 		= -I./includes -I./libft
CRITERION		= -lcriterion
LIBS			= -Llibft -lft -lncurses
LIBFT 			= libft/libft.a
NAME			= Minishell

RST				= "\e[0m"
RED				= "\e[31m"
GREEN			= "\e[32m"

PATH_SRCS		= ./srcs/
RAW_SRCS		= builtin_cd.c \
				  builtin_env.c \
				  builtin_export.c \
				  builtin_exit.c \
				  builtin_pwd.c \
				  builtin_unset.c \
				  builtin_utils.c \
				  dict_utils.c \
				  env_utils.c \
				  error.c \
				  exec.c \
				  exec_builtin.c \
				  flagger.c \
				  get_next_line.c \
				  get_next_line_utils.c \
				  globals.c \
				  input.c \
				  parse_command.c \
				  path_utils.c \
				  token.c \
				  token_eval.c \
				  token_fcts.c \
				  token_quote_removal.c \
				  token_utils.c \
				  env_expansion.c \

SRCS			= main.c $(addprefix srcs/, $(RAW_SRCS))
OBJS 			= $(SRCS:.c=.o)
NO_MAIN			= $(filter-out main.o,$(OBJS))

TEST			= minishell_test
TEST_RAW_SRCS	= test_helpers.c \
				  builtin_cd_tests.c \
				  builtin_export_tests.c \
				  builtin_pwd_tests.c \
				  builtin_unset_tests.c \
				  builtin_utils_tests.c \
				  env_test.c \
				  env_utils_tests.c \
				  dict_utils_tests.c \
				  exec_builtin_tests.c \
				  exec_tests.c \
				  inputs_correct.c \
				  path_utils_tests.c \
				  quotes_tests.c \
				  token_eval_tests.c \
				  tokenizer_ftests.c \
				  tokenizer_tests.c \
				  tokens_tests.c \
				  utils_tests.c \

TEST_SRCS		= $(addprefix tests/,$(TEST_RAW_SRCS))
TEST_OBJS 		= $(TEST_SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo $(GREEN)"Compiling Minishell executable ..."$(RST)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo $(GREEN)"Minishell is ready !\nEnter \"./Minishell\" for execution."$(RST)

$(LIBFT):
	@echo $(GREEN)"Compiling libft ..."$(RST)
	@$(MAKE) bonus -C libft

test: $(TEST)
	./$(TEST) --jobs 1
	$(RM) *.test

$(TEST): $(NO_MAIN) $(TEST_OBJS) $(LIBFT)
	$(CC) $(NO_MAIN) $(TEST_OBJS) $(CRITERION) $(LIBS) -o $(TEST)
	$(RM) $(TEST_OBJS)

clean:
	@echo $(RED)"Removing objects and librairies ..."$(RST)
	@$(RM) $(OBJS)
	@$(MAKE) fclean -C libft

fclean: clean
	@echo $(RED)"Removing minishell and tests ..."$(RST)
	@$(RM) $(NAME) $(TEST) ${TEST_OBJS} $(LIBFT)

re: fclean all

.PHONY: all clean fclean re test
