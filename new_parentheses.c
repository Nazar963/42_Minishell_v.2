/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parentheses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:57:39 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/06 11:02:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_piece(int f, int l, t_shell_stuff *sh)
{
	char	*new_str;
	int		i;
	int		j;

	shft_init_two_vars(&i, 0, &j, 0);
	new_str = ft_calloc(ft_strlen(loco()->piece) - (l - f) + 1, sizeof(char));
	while (loco()->piece[i])
	{
		if (i == f)
		{
			while (i != l)
				i++;
			i++;
		}
		if (j == f)
		{
			if (sh->lststatus == 0)
				new_str[j++] = '0';
			else
				new_str[j++] = '1';
		}
		new_str[j++] = loco()->piece[i++];
	}
	free(loco()->piece);
	return (new_str);
}

void	clean_loco_piece(int first_index, int last_index)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = (char *)ft_calloc(ft_strlen(loco()->piece), sizeof(*new_str));
	if (!new_str)
		return ;
	while (loco()->piece[i])
	{
		if (i == first_index)
			while (i <= last_index)
				i++;
		new_str[j++] = loco()->piece[i++];
	}
	free(loco()->piece);
	loco()->piece = new_str;
}

char	*cmd_pare_clean(char *cmd)
{
	int		i;
	int		j;
	int		x;
	char	*new_str;

	i = 0;
	j = 0;
	x = pare()->index;
	new_str = ft_calloc(ft_strlen(cmd), sizeof(char));
	while (shft_istab(loco()->piece[i]))
		i++;
	if (loco()->piece[i] == '0')
		new_str[j++] = '0';
	while (cmd[x])
	{
		new_str[j++] = cmd[x++];
	}
	free(cmd);
	return (new_str);
}

char	*split_one_cmd(char *cmd)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)ft_calloc(ft_strlen(cmd) + 2, sizeof(char));
	while (cmd[i] && cmd[i] != '&'
		&& cmd[i + 1] != '&' && cmd[i] != '|' && cmd[i + 1] != '|')
		new_str[j++] = cmd[i++];
	return (new_str);
}

void	command_parentheses_clean_1(char *cmd, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == '(')
		{
			if (cmd[i] == '(' && pare()->first == 0)
				pare()->first = i;
			pare()->controll++;
		}
		if (cmd[i] == ')')
		{
			if (pare()->controll == 1)
			{
				pare()->last = i;
				break ;
			}
			else
				pare()->controll--;
		}
		i++;
	}
}
