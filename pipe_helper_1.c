/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:46:25 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/13 18:41:42 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tempfile_creat(int doset)
{
	int	tempfd;

	tempfd = open(".tempfile", 01101, 0666);
	if (doset)
		dup2(tempfd, STDOUT_FILENO);
	tempfd = open(".tempfile", O_RDONLY);
	dup2(tempfd, STDIN_FILENO);
	return ;
}

char	*fork_doer(int doset, int fd[2], char *tmp, t_shell_stuff *sh)
{
	if (doset)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	}
	if (shft_is_builtin(tmp) && !shft_redirections(&tmp, sh, &doset))
		sh->lststatus = command_nobonus(tmp, sh);
	sh->doexit = 1;
	loco()->sigstop = 1;
	sh->exit_code = sh->lststatus;
	return (tmp);
}

char	*shft_ft_tp_helper_nobonus(int pipes, t_shell_stuff *sh,
		int doset, char *tmp)
{
	int			fd[2];
	static int	from_last = 0;

	tmp = check_for_wildcard_normal(tmp);
	shft_clean_pars_nobonus(tmp);
	if (shft_is_builtin(tmp) == 0 && !shft_redirections(&tmp, sh, &doset))
		return (sh->lststatus = builtin_cmds(tmp, sh, doset), tmp);
	loco()->lastcng = pipe(fd) * 0;
	loco()->p[pipes] = fork();
	if (loco()->p[pipes])
	{
		if (doset)
		{
			dup2(fd[0], STDIN_FILENO);
			if (from_last)
				close(from_last);
			from_last = fd[0];
			if (!doset)
				from_last = 0;
			return (close(fd[1]), tmp);
		}
		return (close(from_last), tmp);
	}
	return (fork_doer(doset, fd, tmp, sh));
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
