/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:23:47 by pcharton          #+#    #+#             */
/*   Updated: 2021/04/17 19:23:47 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main(int argc, char *argv[], char *envp[])
{
	char **save;

	save = ft_tabdup(envp);
	while (*save)
	{
		printf("%s\n", *save);
		*save++;
	}
}