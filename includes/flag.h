/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:48:51 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/25 16:29:55 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_H
# define FLAG_H

# define IS_QUOTED	0x10
# define BACKSLASH 0x11
# define SINGLE_QUOTES 0x12
# define DOUBLE_QUOTES 0x14
# define MIXED_QUOTES 0x16
# define QUOTING_ERROR 0x40

int		check_quoting(char *word);
void	update_flag_count(int *flag, int *count);

#endif
