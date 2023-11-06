/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parentheses_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:59:36 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/06 11:02:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recursive_cleanup(char *cmd, int *i)
{
	char	*zoro;

	recursive_cleanup_init();
	while (pare()->flag == 0)
	{
		(*i) = recursive_cleanup_2(cmd, i);
		if (cmd[(*i)] == '(')
		{
			(*i) = recursive_cleanup_1(cmd, i);
			if (cmd[(*i)] == '|')
				cmd = shit(ft_strdup_fr_to(cmd, (*i), ft_strlen(cmd)), i);
			else
				pare()->flag = 1;
		}
		else
		{
			(*i) = recursive_cleanup_3(cmd, i);
			if (cmd[(*i)] == '|')
				cmd = shit(ft_strdup_fr_to_free(cmd, (*i), ft_strlen(cmd)), i);
			else
				pare()->flag = 1;
		}
	}
	zoro = ft_strdup(cmd);
	return (free(cmd), zoro);
}

char	*remove_status_operator_cmd(char *cmd)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = recursive_cleanup(cmd, &i);
	cmd = ft_strdup(new_str);
	free(new_str);
	new_str = (char *)ft_calloc(ft_strlen(cmd), sizeof(char));
	while (cmd[i] && (cmd[i] == '&' || cmd[i] == '|' || shft_istab(cmd[i])))
		i++;
	while (cmd[i])
		new_str[j++] = cmd[i++];
	free(cmd);
	return (new_str);
}

char	*status_check_and_clean(char *cmd)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = (char *)ft_calloc(ft_strlen(cmd), sizeof(char));
	if (cmd[0] == '0')
	{
		while (cmd[i])
		{
			if (cmd[i] == '&' && cmd[i] == '&')
				return (remove_status_operator(cmd));
			else if (cmd[i] == '|' && cmd[i + 1] == '|')
				return (remove_status_operator_cmd(cmd));
			i++;
		}
	}
	while (cmd[i])
	{
		if (cmd[i] == '&' && cmd[i + 1] == '&')
			return (remove_status_operator_cmd(cmd));
		else if (cmd[i] == '|' && cmd[i + 1] == '|')
			return (remove_status_operator(cmd));
		i++;
	}
	return (new_str);
}

char	*handle_exec_pare(t_shell_stuff *sh, int *pp, int doset, char *cmd)
{
	char	*splitted_cmd;

	while (shft_strchr(cmd, '(', '\'', '\"'))
	{
		splitted_cmd = split_one_cmd(cmd);
		while (shft_strchr(splitted_cmd, '(', '\'', '\"'))
		{
			cmd = command_parentheses_clean(cmd);
			pare()->first = 0;
			pare()->last = 0;
			pare()->controll = 0;
			splitted_cmd = splitted_command_parentheses_clean(splitted_cmd);
		}
		splitted_cmd = check_for_wildcard_normal(splitted_cmd);
		executed_command(sh, pp, doset, splitted_cmd);
		cmd = status_adding_cmd_cleaning(cmd, sh);
		cmd = status_check_and_clean(cmd);
		free(splitted_cmd);
	}
	return (cmd);
}

char	*check_for_parentheses(char *cmd, t_shell_stuff *sh, int *pp, int doset)
{
	if (shft_strchr(loco()->piece, '(', '\'', '\"'))
	{
		cmd = handle_exec_pare(sh, pp, doset, cmd);
		loco()->index = ft_strlen(loco()->piece);
		loco()->parentheses = 1;
		return (cmd);
	}
	return (cmd);
}
