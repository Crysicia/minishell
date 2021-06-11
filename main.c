/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:45:25 by lpassera          #+#    #+#             */
/*   Updated: 2021/06/11 19:32:35 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	run_minishell(void)
{
	t_list	*input_list;
	char	*input_str;
	int		ret;

	while (1)
	{
		signal(SIGINT, handle_sigint);
		input_str = readline("minishell: ");
		add_history(input_str);
		input_list = parser_loop(input_str);
		if (!check_syntax_error(input_list))
		{
			ret = evaluation_pass(input_list);
			if (!ret)
				execute_all_the_commands(input_list);
		}
		ft_lstclear(&input_list, free_block);
		free(input_str);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (!init_globals(envp))
		return (1);
	if (argc == 1)
		run_minishell();
	else if ((argc == 3) && check_bash_c_option(argv[1]))
		bash_c_option(argv[2]);
	else
		return (-1);
	destroy_globals();
	return (0);
}
