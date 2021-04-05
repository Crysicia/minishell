/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/04/05 12:18:28 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_prompt(void)
{
	write(1, "minishell>", 10);
}

int	main(int argc, char *argv[], char *envp[])
{	
	while (1)
		print_prompt();
	return (0);
}
