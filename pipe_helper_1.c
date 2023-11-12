/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:46:25 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/12 11:37:18 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	shft_pipemaker(int pipes, char doset)
// {
// }

char	*shft_ft_tp_helper_nobonus(int pipes, t_shell_stuff *sh,
		int doset, char *tmp)
{
	int			fd[2];
	static int	from_last = 0;

	pipe(fd);
	tmp = check_for_wildcard_normal(tmp);
	loco()->p[pipes] = fork();
	if (loco()->p[pipes])
	{
		if (doset)
			dup2(fd[1], STDOUT_FILENO);
		if (shft_is_builtin(tmp) == 0 && !shft_redirections(&tmp, sh))
			sh->lststatus = builtin_cmds(tmp, sh) + close(fd[0] * 0);
		if (doset)
		{
			dup2(fd[0] + close(fd[1]) * 0, STDIN_FILENO);
			if (from_last)
				close(from_last);
			from_last = fd[0];
			if (!doset)
				from_last = 0;
		}
		else
			close(from_last);
		return (tmp);
	}
	if (doset)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	}
	if (shft_is_builtin(tmp) != 0 && !shft_redirections(&tmp, sh))
		sh->lststatus = command_nobonus(tmp, sh);
	sh->doexit = 1;
	loco()->sigstop = 1;
	sh->exit_code = sh->lststatus;
	return (tmp);
}

int	command_fork_nobonus(char **args, t_shell_stuff *sh)
{
	char	**envdp;

	envdp = shft_dupenv(sh);
	execve(args[0], args, envdp);
	shft_putter("minishell: \'", args[0], "\': Is a directory\n", ERRSTD);
	sh->doexit = 1;
	sh->exit_code = 126;
	ft_free_tab(envdp);
	return (0);
}

int	command_fork(char **args, t_shell_stuff *sh, int doset)
{
	int		res;
	pid_t	fpid;
	int		pipefd[2];
	char	**envdp;

	pipe(pipefd);
	fpid = fork();
	loco()->forkpid = fpid;
	if (fpid)
	{
		if (doset)
			dup2(pipefd[0], STDIN_FILENO);
		close (pipefd[1]);
		return (waitpid(fpid, &res, 0), WEXITSTATUS(res));
	}
	if (doset && !loco()->fd_setafter)
		dup2(pipefd[1], STDOUT_FILENO);
	envdp = shft_dupenv(sh);
	close (pipefd[0]);
	execve(args[0], args, envdp);
	shft_putter("minishell: \'", args[0], "\': Is a directory\n", ERRSTD);
	sh->doexit = 1;
	sh->exit_code = 126;
	ft_free_tab(envdp);
	return (0);
}
