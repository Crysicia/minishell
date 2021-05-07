/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/07 18:00:27 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_prompt(void)
{
	write(1, "Minishell>", 10);
}

void	handle_sigint(int signal)
{
	printf("\n");
	if (g_globals->current_pid)
		kill(g_globals->current_pid, signal);
	print_prompt();
}

void	iterate_over_token_list(t_list *list)
{
	t_list	*tmp;
	int		ret;

	ret = 0;
	tmp = list;
	while (tmp && (ret != -1))
		ret = evaluate_token(&tmp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*input_list;
	char	*input_str;

	if (argc != 1)
		return (-1);
	if (!init_globals(envp))
		return (1);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		print_prompt();
		input_str = get_command();
		input_list = parse_to_list(input_str);
		print_token_list(input_list);
		iterate_over_token_list(input_list);
	}
	(void)argv;
	return (0);
}
