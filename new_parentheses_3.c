/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parentheses_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:59:02 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/24 20:07:46 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shit(char *cmd, int *i)
{
	pare()->first = 0;
	pare()->last = 0;
	pare()->controll = 0;
	(*i) = 0;
	while (cmd[(*i)] && cmd[(*i)] != '&'
		&& cmd[(*i) + 1] != '&' && cmd[(*i)] != '|' && cmd[(*i) + 1] != '|')
		(*i)++;
	while (cmd[(*i)] && (cmd[(*i)] == '&'
			|| cmd[(*i)] == '|' || cmd[(*i)] == ' '))
		(*i)++;
	if (cmd[(*i)] == '(')
	{
		(*i) = shit_helper(cmd, i);
		while (cmd[(*i)] && cmd[(*i)] == ' ')
			(*i)++;
	}
	else
	{
		while (cmd[(*i)] && cmd[(*i)] != '&'
			&& cmd[(*i) + 1] != '&' && cmd[(*i)] != '|' && cmd[(*i) + 1] != '|')
			(*i)++;
		while (cmd[(*i)] && cmd[(*i)] == ' ')
			(*i)++;
	}
	return (cmd);
}

int	recursive_cleanup_1(char *cmd, int *i)
{
	while (cmd[(*i)])
	{
		if (cmd[(*i)] == '(')
		{
			if (cmd[(*i)] == '(' && pare()->first == 0)
				pare()->first = (*i);
			pare()->controll++;
		}
		if (cmd[(*i)] == ')')
		{
			if (pare()->controll == 1)
			{
				pare()->last = (*i);
				(*i)++;
				break ;
			}
			else
				pare()->controll--;
		}
		(*i)++;
	}
	while (cmd[(*i)] && cmd[(*i)] == ' ')
		(*i)++;
	return ((*i));
}

void	recursive_cleanup_init(int *loco)
{
	pare()->first = 0;
	pare()->last = 0;
	pare()->controll = 0;
	*loco = 0;
}

int	recursive_cleanup_2(char *cmd, int *i)
{
	pare()->controll = 0;
	(*i) = 0;
	while (cmd[(*i)] && cmd[(*i)] != '&'
		&& cmd[(*i) + 1] != '&' && cmd[(*i)] != '|' && cmd[(*i) + 1] != '|')
		(*i)++;
	while (cmd[(*i)] && (cmd[(*i)] == '&'
			||cmd[(*i)] == '|' || cmd[(*i)] == ' '))
		(*i)++;
	return ((*i));
}

int	recursive_cleanup_3(char *cmd, int *i)
{
	while (cmd[(*i)] && cmd[(*i)] != '&'
		&& cmd[(*i) + 1] != '&' && cmd[(*i)] != '|' && cmd[(*i) + 1] != '|')
		(*i)++;
	while (cmd[(*i)] && cmd[(*i)] == ' ')
		(*i)++;
	return ((*i));
}
