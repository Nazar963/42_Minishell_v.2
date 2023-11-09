/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:21 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/09 20:24:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_or_cleaner_helper(char *new_cmd, char *cmd,
	int *j, int *last_para)
{
	free(new_cmd);
	new_cmd = (char *)ft_calloc(ft_strlen(cmd) - (*last_para) + 2,
			sizeof(char));
	if (!new_cmd)
		return (NULL);
	new_cmd[(*j)++] = '0';
	(*last_para)++;
	while (cmd[(*last_para)])
		new_cmd[(*j)++] = cmd[(*last_para)++];
	free(cmd);
	return (new_cmd);
}

void	parentheses_helper_1(char *cmd, t_shell_stuff *sh,
	int *pp, int doset)
{
	char	*temp;

	temp = ft_split_bonus(cmd, &loco()->index);
	loco()->piece = temp;
	if (shft_strchr(loco()->piece, '(', '\'', '\"'))
	{
		loco()->and = 0;
		loco()->or = 0;
		check_for_operator(loco()->piece);
		check_for_parentheses(cmd, sh, pp, doset);
	}
	else
	{
		loco()->g_and = loco()->and;
		loco()->g_or = loco()->or;
		loco()->and = 0;
		loco()->or = 0;
		check_for_operator(loco()->piece);
	}
}

void	parentheses_helper_2_0(void)
{
	if (loco()->start_flag == 0)
		loco()->first_para = loco()->i;
	loco()->start_flag = 1;
	loco()->count++;
}

void	parentheses_helper_2(char *cmd)
{
	loco()->i = 0;
	while (cmd[loco()->i])
	{
		if (cmd[loco()->i] == '(')
			parentheses_helper_2_0();
		else if (cmd[loco()->i] == ')')
			loco()->count--;
		if (loco()->count == 0 && loco()->start_flag == 1)
			break ;
		loco()->i++;
	}
	loco()->z = loco()->i - 1;
	while (cmd[loco()->z])
	{
		if ((cmd[loco()->z] == '&' && cmd[loco()->z + 1] == '&')
			|| (cmd[loco()->z] == '|' && cmd[loco()->z + 1] == '|'))
			break ;
		else if (cmd[loco()->z] == '|' && cmd[loco()->z + 1] != '|')
			loco()->out_to_pipe = 1;
		if (loco()->out_to_pipe == 1)
			break ;
		loco()->z++;
	}
}

char	*parentheses_helper_3(char *cmd, t_shell_stuff *sh, int *pp, int doset)
{
	char	*temp;

	if (loco()->piece[0] != '0' && loco()->piece[0] != '1')
		sh->lststatus = execution_proccess_or_bonus(pp, sh, doset);
	loco()->i--;
	parentheses_helper_2(cmd);
	free(loco()->piece);
	temp = ft_strdup_len(cmd, loco()->i);
	loco()->piece = temp;
	cmd = cmd_parentheses_or_cleaner(cmd, loco()->first_para, loco()->i, sh);
	return (cmd);
}
