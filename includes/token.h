/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:03:54 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/13 17:47:27 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum	e_token
{
	tok_end_of_cmd = 0,
	tok_pipe = 1,
	tok_redir_l = 2,
	tok_append_r = 3,
	tok_redir_r = 4,
	tok_command = 5
}				t_token;

typedef struct		s_tmp
{
	char			*cmd;
	enum e_token	role;
}					t_tmp;

enum e_token get_next_token(char *str);


#endif
