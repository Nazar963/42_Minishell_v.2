/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:20:48 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/19 16:42:47 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_cleaner(char *tmp, int index, t_shell_stuff *sh)
{
	char	*new_tmp;
	int		i;

	i = 0;
	new_tmp = (char *)ft_calloc(ft_strlen(tmp) - index + 10, sizeof(char));
	if (!new_tmp)
		return (NULL);
	if (sh->lststatus)
		new_tmp[i++] = '1';
	else
		new_tmp[i++] = '0';
	while (tmp[index])
	{
		new_tmp[i++] = tmp[index++];
	}
	free(tmp);
	return (new_tmp);
}

char	*cmd_parentheses_and_cleaner(char *cmd, int first_para, int last_para,
	t_shell_stuff *sh)
{
	char	*new_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_cmd = NULL;
	if (sh->lststatus)
		return (cmd_and_cleaner_helper(new_cmd, cmd, &j, &last_para));
	while (cmd[i] && (cmd[i] != '&' && cmd[i] != '|'))
		i++;
	new_cmd = (char *)ft_calloc(ft_strlen(cmd) - i + 2, sizeof(char));
	new_cmd[j++] = '0';
	while (cmd[i])
	{
		if (i == first_para)
			i++;
		else if (i == last_para)
			i++;
		new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = '\0';
	free(cmd);
	return (new_cmd);
}

char	*cmd_parentheses_or_cleaner(char *cmd, int first_para, int last_para,
	t_shell_stuff *sh)
{
	char	*new_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i] && (cmd[i] != '&' && cmd[i] != '|'))
		i++;
	new_cmd = (char *)ft_calloc(ft_strlen(cmd) - i + 2, sizeof(char));
	if (sh->lststatus == 0)
		return (cmd_or_cleaner_helper((char *)new_cmd, cmd, &j, &last_para));
	if (!new_cmd)
		return (NULL);
	new_cmd[j++] = '1';
	while (cmd[i])
	{
		if (i == first_para)
			i++;
		else if (i == last_para)
			i++;
		new_cmd[j++] = cmd[i++];
	}
	free(cmd);
	return (new_cmd);
}

char	*clearer_lol(char *cmd)
{
	char	*res;
	int		ct;
	int		i;
	int		j;

	ct = 0;
	res = malloc(ft_strlen(cmd) + 1);
	i = 0;
	j = 0;
	while (cmd[i] && cmd[i] != '|' && cmd[i] != '&')
		i++;
	while (cmd[i])
	{
		if (cmd[i] == '(' && !ct++)
			i++;
		if (cmd[i] == ')' && !--ct)
			i++;
		res[j++] = cmd[i++];
	}
	res[j] = '\0';
	free(cmd);
	return (res);
}

char	*check_for_parentheses(char *cmd, t_shell_stuff *sh, int *pp, int doset)
{
	char	*temp;

	if (ft_strchr(loco()->piece, '('))
	{
		loco()->index = 0;
		loco()->parentheses = 1;
		if (loco()->and == 1)
		{
			if (loco()->piece[0] != '0' && loco()->piece[0] != '1')
				sh->lststatus = execution_proccess_and_bonus(pp, sh, doset);
			loco()->i--;
			parentheses_helper_2(cmd);
			free(loco()->piece);
			temp = ft_strdup_len(cmd, loco()->i);
			loco()->piece = temp;
			cmd = cmd_parentheses_and_cleaner(cmd,
					loco()->first_para, loco()->i, sh);
			free(temp);
		}
		else if (loco()->or == 1)
			cmd = parentheses_helper_3(cmd, sh, pp, doset);
		parentheses_helper_1(cmd, sh, pp, doset);
	}
	return (cmd);
}
