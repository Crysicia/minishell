/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharton <pcharton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:48:01 by pcharton          #+#    #+#             */
/*   Updated: 2021/05/05 11:48:01 by pcharton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include "../includes/flag.h"

void	word_flagger(t_token *token)
{
	token->flag = 0;
}