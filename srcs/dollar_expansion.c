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
*/

void	dollar_expansion(t_token *tok)
{
	char	buffer[1024];
	char	*word_ptr;
	char	*buffer_ptr;

	if (tok->role == word && (!(tok->flag) || (tok->flag == DOUBLE_QUOTES)))
	{
		word_ptr = tok->cmd;
		ft_bzero(buffer, 1024);
		buffer_ptr = &buffer[0];
		while (*word_ptr)
		{
			if (*word_ptr == '\\')
				copy_escaped_character(&word_ptr, &buffer_ptr);
			else if (*word_ptr == '$')
				expand_env_variable(&word_ptr, &buffer_ptr);
			else
				*buffer_ptr++ = *word_ptr++;
		}
		tok->cmd = ft_strdup(&buffer[0]);
	}
}
	/*	free(word_ptr); (makes cr segf)*/

void	expand_env_variable(char **str, char **buffer)
{
	t_dict	*env_var;
	char	*var_name;
	size_t	index;

	index = 1;
	while (*(*str + index) && ft_isalnum(*(*str + index)))
		index++;
	var_name = ft_strndup(*str + 1, index - 1);
	env_var = ft_getenv(var_name);
	if (env_var)
	{
		ft_strlcpy(*buffer, env_var->value, ft_strlen(env_var->value) + 1);
		*buffer += ft_strlen(env_var->value);
	}
	free(var_name);
	*str += index;
}

void	copy_escaped_character(char **str, char **buffer)
{
	**buffer = *(*str + 1);
	*buffer += 1;
	*str += 2;
}

/*
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
*/