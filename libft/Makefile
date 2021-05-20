# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/15 11:22:32 by lpassera          #+#    #+#              #
#    Updated: 2021/04/26 10:00:31 by pcharton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR 			= ar rc
CC			= gcc
CFLAGS 		= -Wall -Wextra -Werror
NORMINETTE  = ~/.norminette/norminette.rb
RM 			= rm -f
NAME 		= libft.a
HEADER 		= libft.h

SRCS 		= ft_memset.c \
			  ft_bzero.c \
			  ft_memcpy.c \
			  ft_memccpy.c \
			  ft_memmove.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_strlen.c \
			  ft_isalpha.c \
			  ft_isdigit.c \
			  ft_isalnum.c \
			  ft_isascii.c \
			  ft_isprint.c \
			  ft_toupper.c \
			  ft_tolower.c \
			  ft_strchr.c \
			  ft_strrchr.c \
			  ft_strncmp.c \
			  ft_strlcpy.c \
			  ft_strlcat.c \
			  ft_strnstr.c \
			  ft_strjoin.c \
			  ft_strtrim.c \
			  ft_strjoin_free.c \
			  ft_strcmp.c \
			  ft_strcchr.c \
			  ft_tabdup.c \
			  ft_atoi.c \
			  ft_calloc.c \
			  ft_strdup.c \
			  ft_strndup.c \
			  ft_substr.c \
			  ft_split.c \
			  ft_itoa.c \
			  ft_strmapi.c \
			  ft_putchar_fd.c \
			  ft_putstr_fd.c \
			  ft_putendl_fd.c \
			  ft_putnbr_fd.c \
			  ft_max.c \
			  ft_min.c \
			  ft_free_matrix.c \
			  ft_split_set.c \
			  ft_in_range.c \
			  ft_strcmp.c \
			  ft_isspace.c \

BONUS_SRCS	= ft_lstnew.c \
			  ft_lstnew_safe.c \
			  ft_lstadd_front.c \
 			  ft_lstsize.c \
			  ft_lstlast.c \
			  ft_lstadd_back.c \
			  ft_lstdelone.c \
			  ft_lstclear.c \
			  ft_lstiter.c \
			  ft_lstmap.c \
			  ft_lstsort.c \

OBJS 		= $(SRCS:.c=.o)
BONUS_OBJS 	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME) $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

norme:
	$(NORMINETTE) $(SRCS) $(BONUS_SRCS) $(HEADER)

re: fclean all

.PHONY: all bonus clean fclean norme
