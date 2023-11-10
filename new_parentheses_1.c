/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parentheses_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:58:15 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/10 19:27:11 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_parentheses_clean(char *cmd)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)ft_calloc(ft_strlen(cmd), sizeof(char));
	command_parentheses_clean_1(cmd, i);
	while (cmd[i])
	{
		if (i == pare()->first || i == pare()->last)
			i++;
		new_str[j++] = cmd[i++];
	}
	free(cmd);
	return (new_str);
}

int	splitted_command_parentheses_clean_1(char *splitted_cmd, int *f)
{
	int	i;

	i = 0;
	while (splitted_cmd[i])
	{
		if (splitted_cmd[i] == ')')
			(*f) = i;
		i++;
	}
	return ((*f));
}

char	*splitted_command_parentheses_clean(char *splitted_cmd)
{
	int		i;
	int		j;
	int		check;
	char	*new_str;
	int		find_last_parenthesis;

	shft_init_two_vars(&i, 0, &j, 0);
	check = 0;
	find_last_parenthesis = 0;
	new_str = (char *)ft_calloc(ft_strlen(splitted_cmd), sizeof(char));
	splitted_command_parentheses_clean_1(splitted_cmd, &find_last_parenthesis);
	while (splitted_cmd[i])
	{
		if (splitted_cmd[i] == '(' && check == 0)
		{
			i++;
			check = 1;
		}
		if (find_last_parenthesis != 0 && i == find_last_parenthesis)
			i++;
		if (splitted_cmd[i])
			new_str[j++] = splitted_cmd[i++];
	}
	free(splitted_cmd);
	return (new_str);
}

char	*status_adding_cmd_cleaning(char *cmd, t_shell_stuff *sh)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	while (cmd[i] && cmd[i] != '&' && cmd[i + 1] != '&'
		&& cmd[i] != '|' && cmd[i + 1] != '|')
		i++;
	if (sh->lststatus == 0)
	{
		new_str[j++] = '0';
		new_str[j++] = ' ';
	}
	else if (sh->lststatus)
	{
		new_str[j++] = '1';
		new_str[j++] = ' ';
	}
	while (cmd[i])
		new_str[j++] = cmd[i++];
	free(cmd);
	return (new_str);
}

void	executed_command(t_shell_stuff *sh
	, int *pp, int doset, char *splitted_cmd)
{
	if (sh->doexit != -1 || shft_redirections(&splitted_cmd, sh, &doset))
	{
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
		if (sh->doexit != -1)
			sh->lststatus = 1;
		return ;
	}
	if (shft_is_builtin(splitted_cmd) == 0)
		sh->lststatus = builtin_cmds(splitted_cmd, sh, doset);
	else
		sh->lststatus = command(splitted_cmd, sh, doset);
	if (sh->lststatus == -1)
	{
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
	}
}
