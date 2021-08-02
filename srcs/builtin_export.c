/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:50:15 by lpassera          #+#    #+#             */
/*   Updated: 2021/07/20 17:03:02 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	export_error(char *argument, int code)
{
	t_dict	*dict;
	char	buffer[MAXPATHLEN];

	dict = env_to_dict(argument);
	ft_strlcpy(buffer, "'", 2);
	ft_strlcat(buffer, dict->key, MAXPATHLEN);
	ft_strlcat(buffer, "': not a valid identifier", MAXPATHLEN);
	display_error("export", buffer);
	free_dict(dict);
	return (code);
}

int	dict_key_cmp(void *dict1, void *dict2)
{
	if (!dict1 || !dict2)
		return (0);
	return (ft_strcmp(((t_dict *)dict1)->key, ((t_dict *)dict2)->key));
}

int	display_export(void)
{
	t_list	*list;

	list = ft_lstmap(g_globals->env, dup_dict, free_dict);
	ft_lstsort(&list, dict_key_cmp);
	while (list)
	{
		printf("export %s", ((t_dict *)list->content)->key);
		if (((t_dict *)list->content)->value)
			printf("=\"%s\"", ((t_dict *)list->content)->value);
		printf("\n");
		list = list->next;

	}
	ft_lstclear(&list, free_dict);
	return (SUCCESS);
}

int	builtin_export(char **arguments)
{
	t_dict	*dict;
	t_dict	*env;
	int		ret;

	ret = SUCCESS;
	if (!arguments || !*arguments)
		return (display_export());
	while (*arguments && (ret == SUCCESS || ret == ERR_BUILTIN_FAILED))
	{
		if (is_env_valid(*arguments, true))
		{
			dict = env_to_dict(*arguments);
			if (!dict)
				return (ERR_MALLOC_FAILED);
			env = ft_getenv(dict->key);
			if (!(env && (env->value && !dict->value))
				&& ft_setenv(dict->key, dict->value))
				ret = ERR_COULD_NOT_SET_ENV;
			free_dict(dict);
		}
		else
			ret = export_error(*arguments, ERR_BUILTIN_FAILED);
		arguments++;
	}
	return (ret);
}
