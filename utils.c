/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:01:07 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/11 20:06:24 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"
#include <stddef.h>

int	execution_bonus_helper(char **cmds, int *pp, t_shell_stuff *sh, int doset)
{
	if (sh->doexit != -1 || shft_redirections(&cmds[loco()->counter],
			sh, &doset))
	{
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
		sh->lststatus = 1;
		ft_free_tab(cmds);
		return (69);
	}
	if (shft_is_builtin(cmds[loco()->counter]) == 0)
		sh->lststatus = builtin_cmds(cmds[loco()->counter], sh, doset);
	else
		sh->lststatus = command(cmds[loco()->counter], sh, doset);
	if (sh->lststatus == -1)
	{
		non_executable_handler(cmds[loco()->counter], sh);
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
	}
	return (sh->lststatus);
}

void	control_and_bonus(int *fixer, int *doset, int counter)
{
	if (counter == 0 && *doset == 1)
	{
		*doset = 0;
		*fixer = 1;
	}
	else if (counter == 1 && *fixer == 1 && loco()->n == 0)
	{
		*doset = 1;
		*fixer = 0;
	}
}

char	**execution_and_bonus_helper_1(int doset, char **cmds,
	t_shell_stuff *sh, int *pp)
{
	int	counter;
	int	fixer;

	shft_init_two_vars(&counter, -1, &fixer, 0);
	while (++counter < 2)
	{
		control_and_bonus(&fixer, &doset, counter);
		if (ft_strchr(cmds[0], '('))
			cmds[0] = clean_cmd(cmds[0]);
		if (counter == 2 && sh->lststatus == 1 || sh->lststatus == 127
			|| sh->lststatus == 126 && loco()->exit != 0)
			break ;
		else if (counter == 1 && loco()->parentheses == 1)
			break ;
		else if (loco()->exit == 0)
			loco()->exit = 1;
		loco()->counter = counter;
		if (execution_bonus_helper(cmds, pp, sh, doset) == 69)
			break ;
	}
	return (cmds);
}

char	**execution_or_bonus_helper_1(int doset, char **cmds,
	t_shell_stuff *sh, int *pp)
{
	int	counter;
	int	fixer;

	shft_init_two_vars(&counter, -1, &fixer, 0);
	while (++counter < 2)
	{
		control_and_bonus(&fixer, &doset, counter);
		if (ft_strchr(cmds[0], '('))
			cmds[0] = clean_cmd(cmds[0]);
		if (counter == 1 && sh->lststatus == 0)
			break ;
		else if (counter == 1 && loco()->parentheses == 1)
			break ;
		else if (counter == 0 && (sh->lststatus == 1 || sh->lststatus == 127
				|| sh->lststatus == 126) && loco()->exit != 0)
			continue ;
		else if (loco()->exit == 0)
			loco()->exit = 1;
		loco()->counter = counter;
		if (execution_bonus_helper(cmds, pp, sh, doset) == 69)
			break ;
	}
	return (cmds);
}

char	*cmd_and_cleaner_helper(char *new_cmd, char *cmd,
	int *j, int *last_para)
{
	new_cmd = (char *)ft_calloc(ft_strlen(cmd) - (*last_para) + 2,
			sizeof(char));
	if (!new_cmd)
		return ((void *)0);
	new_cmd[(*j)++] = '1';
	(*last_para)++;
	while (cmd[(*last_para)])
		new_cmd[(*j)++] = cmd[(*last_para)++];
	free(cmd);
	return (new_cmd);
}

char	*cmd_or_cleaner_helper(char *new_cmd, char *cmd,
	int *j, int *last_para)
{
	new_cmd = (char *)ft_calloc(ft_strlen(cmd) - (*last_para) + 2,
			sizeof(char));
	if (!new_cmd)
		return ((void *)0);
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

	temp = loco()->piece;
	temp = ft_split_bonus(cmd, &loco()->index);
	free(loco()->piece);
	if (ft_strchr(loco()->piece, '('))
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

void	parentheses_helper_2(char *cmd)
{
	while (cmd[++loco()->i])
	{
		if (cmd[loco()->i] == '(')
		{
			if (loco()->start_flag == 0)
				loco()->first_para = loco()->i;
			loco()->start_flag = 1;
			loco()->count++;
		}
		else if (cmd[loco()->i] == ')')
			loco()->count--;
		if (loco()->count == 0 && loco()->start_flag == 1)
			break ;
	}
	loco()->z = loco()->i - 1;
	while (cmd[++loco()->z])
	{
		if ((cmd[loco()->z] == '&' && cmd[loco()->z + 1] == '&')
			|| (cmd[loco()->z] == '|' && cmd[loco()->z + 1] == '|'))
			break ;
		else if (cmd[loco()->z] == '|' && cmd[loco()->z + 1] != '|')
			loco()->out_to_pipe = 1;
		if (loco()->out_to_pipe == 1)
			break ;
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

char	*shft_ft_tp_helper(int *pp, t_shell_stuff *sh, int doset, char *tmp)
{
	if (ft_strchr(tmp, ')') && !ft_strchr(tmp, '('))
		tmp = clean_cmd(tmp);
	if (loco()->g_or == 1 && sh->lststatus == 0)
		return ((void *)0);
	tmp = check_for_wildcard_normal(tmp);
	if (sh->doexit != -1 || shft_redirections(&tmp, sh, &doset))
	{
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
		sh->lststatus = 1;
		return (free(tmp), (void *)0);
	}
	if (shft_is_builtin(tmp) == 0)
		sh->lststatus = builtin_cmds(tmp, sh, doset);
	else
		sh->lststatus = command(tmp, sh, doset);
	if (sh->lststatus == -1)
	{
		non_executable_handler(tmp, sh);
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
	}
	return (tmp);
}

char	*shft_ft_tp_helper_1(int *pp, t_shell_stuff *sh, int doset, char *tmp)
{
	char	*temp;

	temp = check_for_wildcard_normal(loco()->piece);
	loco()->piece = temp;
	tmp = check_for_parentheses(tmp, sh, &pp[0], doset);
	if (loco()->and)
		sh->lststatus = execution_proccess_and_bonus(&pp[0], sh, doset);
	else if (loco()->or)
		sh->lststatus = execution_proccess_or_bonus(&pp[0], sh, doset);
	tmp = cmd_cleaner(tmp, loco()->index, sh);
	if (loco()->parentheses != 1 && (loco()->g_and == 1 || loco()->g_or == 1))
	{
		loco()->g_and = 0;
		loco()->g_or = 0;
	}
	else if (loco()->parentheses != 1)
	{
		loco()->g_and = loco()->and;
		loco()->g_or = loco()->or;
	}
	loco()->and = 0;
	loco()->or = 0;
	free(loco()->piece);
	loco()->out_to_pipe = 0;
	return (tmp);
}
