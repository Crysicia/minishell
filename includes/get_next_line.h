/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:26:48 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/06 14:38:28 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

int		gnl_strchr(char *str, char c);
size_t	gnl_strlen(char *str, int value);
char	*gnl_strdup(char *str, int value);
char	*gnl_join(char *s1, char *s2);
void	gnl_strcpy_and_fill(char *dest, char *source);

int		gnl_read(int fd, char **line, char *buffer);
int		get_next_line(int fd, char **line);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif
#endif
