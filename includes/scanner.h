/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 01:10:52 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/15 12:08:11 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H
# include <stdbool.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "finite_state_machine.h"

char	*ft_strndup(char *str, size_t n);
bool	ft_is_lowercase(int c);
bool	is_space(int c);
bool	is_control_operator(int c);
bool	is_keyword_character(int c);
bool	is_argument_character(int c);
bool	are_quotes_valid(char *line);

size_t	keyword_len(char *line);
size_t	option_len(char *line);
size_t	argument_len(char *line);
size_t	command_len(char *line);

#endif
