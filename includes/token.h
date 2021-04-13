/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:03:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/13 16:45:42 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

enum e_token
{
	end_of_cmd = 0,
	pipe = 1,
	redir_l = 2,
	append_r = 3,
	redir_r = 4,
	command = 5
};

typedef struct		s_tmp
{
	char			*cmd;
	enum e_token	role;
}					t_tmp;

enum e_token get_next_token(char *str);


#endif
