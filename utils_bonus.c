/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:01:07 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/21 18:07:01 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shft_ft_tp_helper(int *pp, t_shell_stuff *sh, int doset, char *tmp)
{
	if (shft_strchr(tmp, ')', '\'', '\"') || shft_strchr(tmp, '(', '\'', '\"'))
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
