/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:01:07 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/10 23:32:23 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

int	execution_and_bonus_helper(char **cmds, int *pp, t_shell_stuff *sh, int doset)
{
	if (sh->doexit != -1 || shft_redirections(&cmds[1], sh, &doset))
	{
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
		sh->lststatus = 1;
		return (69);
	}
	if (shft_is_builtin(cmds[1]) == 0)
		sh->lststatus = builtin_cmds(cmds[1], sh, doset);
	else
		sh->lststatus = command(cmds[1], sh, doset);
	if (sh->lststatus == -1)
	{
		non_executable_handler(cmds[1], sh);
		pipe(pp);
		close(*(pp + 1));
		dup2(*pp, STDIN_FILENO);
	}
	return (sh->lststatus);
}