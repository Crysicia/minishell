/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:26:48 by pcharton          #+#    #+#             */
/*   Updated: 2020/07/03 16:18:01 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

int		ft_strchr(char *str, char c);
size_t	ft_strlen(char *str, int value);
char	*ft_strdup(char *str, int value);
char	*ft_join(char *s1, char *s2);
void	ft_strcpy_and_fill(char *dest, char *source);

int		ft_read(int fd, char **line, char *buffer);
int		get_next_line(int fd, char **line);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif
#endif
