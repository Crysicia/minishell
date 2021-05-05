/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:48:51 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/05 12:48:51 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG__H
# define FLAG_H

# define IS_QUOTED	0x00000010
# define BACKSLASH 0x00000011
# define SINGLE_QUOTES 0x00000012
# define DOUBLE_QUOTES 0x00000014
# define QUOTING_ERROR 0x00000040

int		has_single_quotes(char *str);

# endif
