/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:03 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/10 19:27:54 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_bonus_helper(char **cmds, int *pp, t_shell_stuff *sh, int doset)
{
	if (sh->doexit != -1 || shft_redirections(&cmds[loco()->counter],
			sh, &doset))
	{
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
		if (sh->doexit != -1)
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
		if (shft_strchr(cmds[0], '(', '\'', '\"'))
			cmds[0] = clean_cmd(cmds[0]);
		if (counter == 1 && (sh->lststatus == 1 || sh->lststatus == 127
				|| sh->lststatus == 126) && loco()->exit != 0)
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
		if (shft_strchr(cmds[0], '(', '\'', '\"'))
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
