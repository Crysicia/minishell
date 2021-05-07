/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:36:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/29 15:50:00 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/flag.h"

/* roadmap for quotes
 flagger to know if word is quoted 
 perform $expansion within double quotes and no quotes
 perform complex expqnsion within mixed quotes
 remove quotes
 eventually add the new words to the linked list
*/

/*
	Performing $expansion
	does it need to check if expansion can be done or is it already assumed ?
	strcpy() before after $var
	check var name (alphanumeric len, no \before)
	getenv(var)
	write in buffer (while adding \ to \ and "(why ?))

	remove quotes (now ?)
	remove antislash (now ?)

void	expand_env_variable(char *str, char *buffer)
{
	char	tmp;
	char	*env_var;
	size_t	index;

	index = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	tmp = str[i];
	str[i] = 0;
	env_var = ft_getenv(str);
	if (env_var)
		ft_strlcpy(buffer, env_var, ft_strlen(env_var));
}

*/

/*
	Not sure i need this fct ..
*/

void	dollar_expansion(t_token *tok)
{
	if (tok->role == word && (!(tok->flag) || (tok->flag == DOUBLE_QUOTES)))
		(void)tok;
}

int	copy_single_quoted_text(char *str, char *buffer)
{
	char	*start;

	start = str;
	str++;
	while (*str && (*str != '\''))
		str++;
	if ((str - start) == (unsigned int)ft_strlen(start))
		return (-1);
	else
		return (ft_strlcpy(buffer, start, str - start));
}
