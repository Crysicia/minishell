/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:50:15 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/21 16:57:48 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int builtin_export(char *argument)
{
	t_dict *dict;
	t_dict *env;
	int ret;

	ret = 0;
	dict = env_to_dict(argument);
	if (!dict)
		return (-1);
	env = ft_getenv(dict->key);
	if (env && (env->value && !dict->value))
		;
	else if (ft_setenv(dict->key, dict->value))
		ret = -1;
	free_dict(dict);
	return (ret);
}
