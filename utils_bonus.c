/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:01:07 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/10 19:27:55 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shft_ft_tp_helper(int *pp, t_shell_stuff *sh, int doset, char *tmp)
{
	if (shft_strchr(tmp, ')', '\'', '\"')
		|| shft_strchr(tmp, '(', '\'', '\"'))
		tmp = clean_cmd(tmp);
	if (loco()->g_or == 1 && sh->lststatus == 0)
		return ((void *)0);
	tmp = check_for_wildcard_normal(tmp);
	if (sh->doexit != -1 || shft_redirections(&tmp, sh, &doset))
	{
		piperlol(pp);
		if (sh->doexit != -1)
			sh->lststatus = 1;
		return (free(tmp), (void *)0);
	}
	if (shft_is_builtin(tmp) == 0)
		sh->lststatus = builtin_cmds(tmp, sh, doset);
	else
		sh->lststatus = command(tmp, sh, doset);
	if (sh->lststatus == -1)
	{
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
	}
	return (tmp);
}

char	*shft_ft_tp_helper_1(int *pp, t_shell_stuff *sh, int ds, char *tmp)
{
	char	*temp;

	temp = shft_very_lol();
	if (shft_strchr(loco()->piece, '(', '\'', '\"'))
	{
		tmp = check_for_parentheses(tmp, sh, &pp[0], ds);
		if (!tmp || !*tmp)
			return (shft_ft_tp_hleper_1_0(), free(temp), tmp);
		temp = ft_split_bonus(tmp, &loco()->index);
		temp = check_for_wildcard_normal(temp);
		shft_ft_tp_hleper_1_1(temp);
		if (loco()->and == 0 && loco()->or == 0 && loco()->parentheses == 1)
			sh->lststatus = executed_command_last(sh, pp, ds, loco()->piece);
		loco()->parentheses = 0;
	}
	loco()->n = pare()->flag;
	check_for_operator(loco()->piece);
	if (loco()->and)
		sh->lststatus = execution_proccess_and_bonus(&pp[0], sh, ds);
	else if (loco()->or)
		sh->lststatus = execution_proccess_or_bonus(&pp[0], sh, ds);
	tmp = cmd_cleaner(tmp, loco()->index, sh);
	dup2(sh->tempfds[1], STDOUT_FILENO);
	dup2(sh->tempfds[0], STDIN_FILENO);
	return (shft_ft_tp_hleper_1_0(), free(temp), tmp);
}

int	execution_proccess_and_nizz(int *pp, t_shell_stuff *sh, int doset)
{
	char	**cmds;

	cmds = ft_split_operators(pare()->pare_piece);
	if (cmds[0][0] == '1')
		return (ft_free_tab(cmds), sh->lststatus);
	else if (cmds[0][0] == '0')
	{
		if (cmds[1][0] == '0')
			return (sh->lststatus);
		loco()->counter = 1;
		if (execution_bonus_helper(cmds, pp, sh, doset) == 69)
			return (sh->lststatus);
	}
	else
		cmds = execution_and_bonus_helper_1(doset, cmds, sh, pp);
	ft_free_tab(cmds);
	return (sh->lststatus);
}

int	execution_proccess_or_nizz(int *pp, t_shell_stuff *sh, int doset)
{
	char	**cmds;

	cmds = ft_split_operators(pare()->pare_piece);
	if (cmds[0][0] == '0')
		return (ft_free_tab(cmds), sh->lststatus);
	else if (cmds[0][0] == '1')
	{
		loco()->counter = 1;
		if (execution_bonus_helper(cmds, pp, sh, doset) == 69)
			return (sh->lststatus);
	}
	else
		cmds = execution_or_bonus_helper_1(doset, cmds, sh, pp);
	ft_free_tab(cmds);
	return (sh->lststatus);
}

/* -Werror -Wextra: variable 'temp' set but not used (solved by void cast) --*/
char	*shft_ft_tp_helper_nizz(int *pp,
	t_shell_stuff *sh, int doset, char *tmp)
{
	char	*temp;

	temp = check_for_wildcard_normal(tmp);
	(void)temp;
	if (loco()->and)
		sh->lststatus = execution_proccess_and_nizz(pp, sh, doset);
	else if (loco()->or)
		sh->lststatus = execution_proccess_or_nizz(pp, sh, doset);
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
	free(pare()->pare_piece);
	loco()->out_to_pipe = 0;
	return (tmp);
}
