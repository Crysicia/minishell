CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
RM 				= rm -f
HEADERS 		= -I./includes
CRITERION		= -lcriterion
NAME			= Minishell
SRCS			= main.c \
				  example.c
OBJS 			= $(SRCS:.c=.o)
NO_MAIN			= $(filter-out main.o,$(OBJS))
TEST			= minishell_test
TEST_SRCS		= tests/example_test.c
TEST_OBJS 		= $(TEST_SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

test: $(TEST)
	$(TEST)

$(TEST): $(NO_MAIN) $(TEST_OBJS)
	$(CC) $(NO_MAIN) $(TEST_OBJS) $(CRITERION) -o $(TEST)
	$(RM) $(TEST_OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
