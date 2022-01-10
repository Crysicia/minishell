/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:12:33 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/23 13:34:24 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*dup_dict(void *dict_ptr)
{
	t_dict	*dict;

	dict = dict_ptr;
	if (!dict)
		return (NULL);
	return (new_dict(dict->key, dict->value));
}

t_dict	*env_to_dict(char *env)
{
	t_dict	*dict;
	char	*key;
	char	*delimiter;

	delimiter = ft_strchr(env, '=');
	if (!delimiter)
		dict = new_dict(env, NULL);
	else
	{
		key = ft_strndup(env, (int)(delimiter - env));
		dict = new_dict(key, &delimiter[1]);
		free(key);
		key = NULL;
	}
	return (dict);
}

char	*dict_to_env(t_dict *dict)
{
	char	*env;
	size_t	env_len;

	env_len = ft_strlen(dict->key) + 1;
	if (dict->value)
		env_len += ft_strlen(dict->value) + 1;
	env = malloc(env_len * sizeof(char));
	if (!env)
		return (NULL);
	ft_strlcpy(env, dict->key, ft_strlen(dict->key) + 1);
	if (dict->value)
	{
		ft_strlcat(env, "=", env_len);
		ft_strlcat(env, dict->value, env_len);
	}
	return (env);
}

void	free_dict(void *elem)
{
	t_dict	*dict;

	dict = elem;
	free(dict->key);
	dict->key = NULL;
	free(dict->value);
	dict->value = NULL;
	free(dict);
	dict = NULL;
}

t_dict	*new_dict(char *key, char *value)
{
	t_dict	*dict;

	if (!key)
		return (NULL);
	dict = malloc(sizeof(t_dict));
	if (!dict)
		return (NULL);
	dict->key = ft_strdup(key);
	dict->value = NULL;
	if (value)
		dict->value = ft_strdup(value);
	if (!dict->key || (value && !dict->value))
	{
		free_dict(dict);
		return (NULL);
	}
	return (dict);
}
