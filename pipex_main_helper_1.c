/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_helper_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:23:59 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/19 15:38:48 by naal-jen         ###   ########.fr       */
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
	if (fpid)
	{
		if (doset)
			dup2(pipefd[0], STDIN_FILENO);
		close (pipefd[1]);
		waitpid(fpid, &res, 0);
		return (WEXITSTATUS(res));
	}
	if (doset)
		dup2(pipefd[1], STDOUT_FILENO);
	envdp = shft_dupenv(sh);
	close (pipefd[0]);
	execve(args[0], args, envdp);
	shft_putter("minishell: \'", args[0], "\': Is a directory\n", STDERR_FILENO);
	sh->doexit = 1;
	sh->exit_code = 126;
	ft_free_tab(envdp);
	return (0);
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
	if (ft_strchr(args[0], '/') && access(args[0], X_OK) == 0)
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
	ft_free_tab(args);
	return (res);
}

char	*shft_get_word(char *in)
{
	char	test;
	char	*res;
	int		i;

	test = 0;
	i = 0;
	res = malloc(sizeof(char ) * 999);
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

void	clean_stuff(char *s, int l)
{
	*(s++) = -1;
	while (shft_istab(*s) || *s == '\'' || *s == '\"')
		*(s++) = -1;
	while (*s == '\'' || *s == '\"' || l--)
		*(s++) = -1;
}