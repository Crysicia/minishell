/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:36:29 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/29 15:34:19 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"



void	expansion_flagger(char *str)
{
	if ()
}


/*
  strcpy() before after $var
  check var (alphanumeric len, no \before)
  getenv(var)
  write in buffer while adding \ to \ and "

  remove quotes
  remove antislash
 */

int		copy_single_quoted_text(char *str, char *buffer,
								int *str_index, int *buffer_index)
{
	char	start;

	start = str;
	str++;
	while (*str && (*str != '\''))
	{
		if (*str == '\\')
			str++;
		str++;
	}
	if ((str - start) == ft_strlen(start))
		return (-1);
	else
		return (ft_strlcpy(start, buffer, str - start));
}

char *go_to_unescaped_char(char *str, char target)
{
	size_t index;
	bool escaped;

	index = 0;
	escaped = false;
	while (str[index])
	{
		if (str[index] == target && !escaped)
			return (&str[index + 1]);
		if (str[index] == '\\')
			escaped = !escaped;
		else
			escaped = false;
		index++;
	}
	return (NULL);
}

void	handle_quoting(char *str)
{
	size_t	str_index;
	size_t	buffer_index;
	char	buffer[4096];

	str_index = 0;
	buffer_index= 0;
	ft_bzero(buffer, 4096);
	while (str[str_index] && (str_index < 4096))
	{
		if (is_space(str[str_index]))
		{
			buffer[buffer_index++] = str[str_index++];
			while (is_space(str[str_index]))
				str_index++;
		}
		else if (str[str_index] == '"')
			;
		else if (str[str_index] == '\'')
		{
			str = go_to_unescaped_char(&srt[str_index], '\'');
			if (str == NULL)
				;// SYNTAX ERROR
		}

		else if (str[str_index] == '\\')
		{
			buffer[buffer_index++] = str[str_index++];
			if (str[str_index])
				buffer[buffer_index++] = str[str_index++];
			else
				printf("Minishell error: No character after '\'\n");
		}


		else if (str[str_index] == '$')
		{
			;
		}
	}
	//
	// check tous les caracteres

}
