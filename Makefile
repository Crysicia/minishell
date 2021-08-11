SHELL			= /bin/sh
.SUFFIXES:
.SUFFIXES:		.c .o .a
CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
RM 				= rm -f
HEADERS 		= -I./includes -I./libft
CRITERION		= -lcriterion
LIBS			= -Llibft -lft -lreadline
LIBFT 			= libft/libft.a
NAME			= minishell

RST				= "\e[0m"
RED				= "\e[31m"
GREEN			= "\e[32m"

PATH_SRCS		= ./srcs/
RAW_SRCS		= builtin_cd.c \
				  builtin_echo.c \
				  builtin_env.c \
				  builtin_export.c \
				  builtin_exit.c \
				  builtin_pwd.c \
				  builtin_unset.c \
				  builtin_utils.c \
				  commands.c \
				  dict_utils.c \
				  dollar_expansion.c \
				  env_utils.c \
				  error.c \
				  evaluation.c \
				  exec.c \
				  exec_utils.c \
				  exec_builtin.c \
				  flagger.c \
				  flagger_utils.c \
				  ft_exit.c \
				  file_descriptor.c \
				  globals.c \
				  global_pids.c \
				  heredoc.c \
				  input.c \
				  parse_command.c \
				  parser.c \
				  parser_block.c \
				  parser_utils.c \
				  path_utils.c \
				  redirections.c \
				  pipeline_v3.c \
				  pipelines.c \
				  pipe_utils.c \
				  pipe_utils_free.c \
				  print_debug.c \
				  quoting.c \
				  quoting_double.c \
				  syntax_check.c \
				  token.c \
				  token_fcts.c \
				  token_utils.c \
				  get_next_line.c \
				  get_next_line_utils.c

SRCS			= main.c $(addprefix srcs/, $(RAW_SRCS))
OBJS 			= $(SRCS:.c=.o)
DEBUG			= $(addprefix debug/, $(OBJS))
NO_MAIN			= $(filter-out main.o,$(OBJS))

TEST			= minishell_test
TEST_RAW_SRCS	= test_helpers.c \
				  builtin_cd_tests.c \
				  builtin_echo_tests.c \
				  builtin_export_tests.c \
				  builtin_pwd_tests.c \
				  builtin_unset_tests.c \
				  builtin_utils_tests.c \
				  env_test.c \
				  env_utils_tests.c \
				  dict_utils_tests.c \
				  exec_builtin_tests.c \
				  exec_tests.c \
				  expansion_tests.c \
				  inputs_correct.c \
				  path_utils_tests.c \
				  parser_tests.c \
				  token_eval_tests.c \
				  tokenizer_tests.c \
				  tokens_tests.c \
				  utils_tests.c \

TEST_SRCS		= $(addprefix tests/,$(TEST_RAW_SRCS))
TEST_OBJS 		= $(TEST_SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) -g -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo $(GREEN)"Compiling minishell executable ..."$(RST)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo $(GREEN)"Minishell is ready !\nEnter \"./minishell\" for execution."$(RST)

$(LIBFT):
	@echo $(GREEN)"Compiling libft ..."$(RST)
	@$(MAKE) bonus -C libft

test: $(TEST)
	./$(TEST) --jobs 1
	$(RM) *.test

$(TEST): $(NO_MAIN) $(TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(NO_MAIN) $(TEST_OBJS) $(CRITERION) $(LIBS) -o $(TEST)
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
