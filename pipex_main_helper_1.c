/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_helper_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:23:59 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/10 19:28:53 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	shft_after_setter(void)
{
	int	fd[2];

	if (loco()->fd_setafter)
	{
		pipe(fd);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	command(char *cmd, t_shell_stuff *sh, int doset)
{
	char		**args;
	char		*xpat;
	int			res;

	args = shft_split2(cmd, ' ', '\'', '\"');
	if (access(args[0], F_OK | R_OK) == -1 && access(args[0], F_OK) == 0)
		return (126 + shft_putter("minishell: \'", args[0],
				"\': Permission denied\n", STDERR_FILENO) * 0);
	if (shft_strchr(args[0], '/', '\'', '\"') && access(args[0], X_OK) == 0)
		res = command_fork(args, sh, doset);
	else
	{
		xpat = search_path(args[0], sh);
		res = -1;
		if (xpat)
		{
			free(args[0]);
			args[0] = xpat;
			res = command_fork(args, sh, doset);
		}
	}
	shft_after_setter();
	if (res == -1)
		non_executable_handler(args[0], sh);
	return (ft_free_tab(args), res);
}

char	*shft_get_word(char *in, char end)
{
	char	test;
	char	*res;
	int		i;

	test = 0;
	i = 0;
	res = malloc(ft_strlen(in) + 2);
	while (shft_istab(*in))
		in++;
	while (*in && (!shft_istab(*in) || test))
	{
		if (*in == '\'' && test != 2)
			test ^= 1;
		else if (*in == '\"' && test != 1)
			test ^= 2;
		else
			res[i++] = *in;
		in++;
	}
	res[i++] = end;
	res[i] = '\0';
	return (res);
}

void	word_clean(char *str, int len)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < len)
		if (str[i] != -1)
			str[j++] = str[i];
	str[j] = '\0';
}
