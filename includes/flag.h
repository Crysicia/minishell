/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:48:51 by pcharton          #+#    #+#             */
/*   Updated: 2021/08/10 11:44:23 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_H
# define FLAG_H

# include <stdbool.h>

# define _NO_QUOTES 0
# define _SINGLE_QUOTES 1
# define _DOUBLE_QUOTES 2
# define _EXPANSION 4

# define IS_QUOTED	0x10
# define BACKSLASH 0x11
# define SINGLE_QUOTES 0x12
# define DOUBLE_QUOTES 0x14
# define MIXED_QUOTES 0x16
# define TO_EXPAND 0x20
# define QUOTING_ERROR 0x40

int		check_quoting(char *token_str);
void	update_flag_count(int *flag, int *count);

void	flag_expansion(char *token_str, int *flag);
void	set_flag(int *flag, int bit);
bool	get_flag(int *flag, int bit);
void	print_flags(int *flag);

void	flag_quoting(char *token_str, int *flag);
char	*flag_next_quote(char quote, int *flagged, char *word);

#endif
