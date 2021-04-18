/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 10:53:54 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/18 16:15:38 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_dict *env_to_dict(char *env)
{
	t_dict *dict;
	char *key;
	char *delimiter;

	delimiter = ft_strchr(env, '=');
	if (!delimiter || (delimiter + 1) == 0)
		dict = new_dict(env, NULL);
	else
	{
		key = ft_strndup(env, (int)(delimiter - env));
		dict = new_dict(key, (char *)(delimiter + 1));
		free(key);
	}
	return (dict);
}

char *dict_to_env(t_dict *dict)
{
	char *env;
	size_t env_len;

	env_len = ft_strlen(dict->key) + ft_strlen(dict->value) + 2;
	env = malloc(env_len * sizeof(char));
	if (!env)
		return (NULL);
	ft_strlcpy(env, dict->key, ft_strlen(dict->key) + 1);
	ft_strlcat(env, "=", env_len);
	ft_strlcat(env, dict->value, env_len);
	return (env);
}

void free_dict(t_dict *dict)
{
	free(dict->key);
	free(dict->value);
	free(dict);
}

t_dict *new_dict(char *key, char *value)
{
	t_dict *dict;

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

t_list	*ft_lstnew_safe(void *content)
{
	t_list	*list;

	list = ft_lstnew(content);
	if (!list)
		free(content);
	return (list);
}

t_list	*array_to_list(char **array)
{
	t_list	*head;
	t_list	*node;
	t_dict	*dict;
	int		i;

	if (!array || !*array)
		return (NULL);
	head = NULL;
	dict = NULL;
	i = 0;
	while (array[i])
	{
		dict = env_to_dict(array[i]);
		node = ft_lstnew_safe(dict);
		if (!dict || !node)
		{
			free_dict(dict);
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		i++;
	}
	return (head);
}

char	**list_to_array(t_list *list)
{
	char	**array;
	size_t	size;
	int		i;

	i = 0;
	size = ft_lstsize(list);
	array = malloc(size * sizeof(char *));
	if (!array)
		return (NULL);
	while (list)
	{
		array[i] = dict_to_env((t_dict *)list->content);
		if (!array[i])
			return (ft_free_matrix((void **)array, i));
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

t_dict	*ft_getenv(const char *name)
{
	t_list	*node;

	node = g_globals->env;
	while (node)
	{
		if (!ft_strcmp(((t_dict *)(node->content))->key, name))
				return ((t_dict *)(node->content));
		node = node->next;
	}
	return (NULL);
}

int		ft_setenv(char *name, char *value)
{
	// Need a strjoin with delimiters to join with = between key and value
	// Then search for an existing env with the same key
	// 	If it exists, change the value
	// 	else add the new variable to the list

	// I think we will need an env structure...
	t_dict *env;
	char *alloc_value;

	if (!name || !value)
		return (-1);
	env = ft_getenv(name);
	if (!env)
		env = new_dict(name, value);
	else
	{
		alloc_value = ft_strdup(value);
		if (alloc_value)
			env->value = alloc_value;
		else
			return (-1);
	}
	if (!env)
		return (-1);
	return (0);
}
