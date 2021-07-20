/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:48:51 by pcharton          #+#    #+#             */
/*   Updated: 2021/07/20 16:37:48 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_H
# define FLAG_H

# define IS_QUOTED	0x10
# define BACKSLASH 0x11
# define SINGLE_QUOTES 0x12
# define DOUBLE_QUOTES 0x14
# define MIXED_QUOTES 0x16
# define TO_EXPAND 0x20
# define QUOTING_ERROR 0x40

int		check_quoting(char *token_str);
void	update_flag_count(int *flag, int *count);
char	*flag_next_quote(char quote, int *flagged, char *word);
int		flag_expansion(char *token_str);
#endif
