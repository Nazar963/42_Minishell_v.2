/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parentheses_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:58:39 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/10 19:27:52 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executed_command_last(t_shell_stuff *sh, int *pp, int doset, char *cmd)
{
	if (sh->doexit != -1 || shft_redirections(&cmd, sh, &doset))
	{
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
		if (sh->doexit != -1)
			sh->lststatus = 1;
		return (sh->lststatus);
	}
	if (shft_is_builtin(cmd) == 0)
		sh->lststatus = builtin_cmds(cmd, sh, doset);
	else
		sh->lststatus = command(cmd, sh, doset);
	if (sh->lststatus == -1)
	{
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
	}
	return (sh->lststatus);
}

void	remove_status_operator_1_1(char *cmd, int i)
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
				i++;
				break ;
			}
			else
				pare()->controll--;
		}
		i++;
	}
}

char	*remove_status_operator_1(char *cmd, char *new_str, int i, int j)
{
	free(new_str);
	new_str = (char *)ft_calloc(ft_strlen(cmd), sizeof(char));
	i = 0;
	j = 0;
	pare()->controll = 0;
	pare()->first = 0;
	pare()->last = 0;
	i += 2;
	while (shft_istab(cmd[i]))
		i++;
	if (cmd[i] == '(')
	{
		remove_status_operator_1_1(cmd, i);
		while (cmd[i])
			new_str[j++] = cmd[i++];
	}
	else
	{
		while (cmd[i] && cmd[i] != '&'
			&& cmd[i + 1] != '&' && cmd[i] != '|' && cmd[i + 1] != '|')
			new_str[j++] = cmd[i++];
	}
	return (new_str);
}

char	*remove_status_operator(char *cmd)
{
	int		i;
	int		j;
	char	*new_str;

	shft_init_two_vars(&i, 0, &j, 0);
	new_str = (char *)ft_calloc(ft_strlen(cmd), sizeof(char));
	while (cmd[i] && cmd[i] != '&'
		&& cmd[i + 1] != '&' && cmd[i] != '|' && cmd[i + 1] != '|')
		i++;
	while (cmd[i] && (cmd[i] == '&' || cmd[i] == '|' || shft_istab(cmd[i])))
		i++;
	while (cmd[i])
		new_str[j++] = cmd[i++];
	if (new_str[0] == '|')
	{
		while (1)
		{
			free(cmd);
			cmd = ft_strdup(new_str);
			new_str = remove_status_operator_1(cmd, new_str, i, j);
			if (new_str[0] == '&')
				break ;
		}
	}
	return (free(cmd), new_str);
}

int	shit_helper(char *cmd, int *i)
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
	return ((*i));
}
