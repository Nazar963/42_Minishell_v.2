/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_helper_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:25:08 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/12 02:17:28 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_stdin(char *limiter, t_shell_stuff *sh, char *hd_name)
{
	int		fd;

	loco()->limiter_flag = 1;
	loco()->limiter_pid = fork();
	if (!loco()->limiter_pid)
	{
		fd = open(hd_name, 01101, 0666);
		pare()->extra = 1;
		pare()->extra_2 = ft_strdup(limiter);
		pare()->child_fd = fd;
		dup2(sh->tempfds[1], STDIN_FILENO);
		sh->doexit = 0;
		return (1);
	}
	waitpid(loco()->limiter_pid, NULL, 0);
	if (loco()->limiter_flag == -2)
		return (1);
	return (0);
}

int	redir_test_access(char *filename, int tempfd, char *cmd)
{
	if (access(filename, R_OK) == -1 && access(filename, F_OK) != -1)
		return (shft_putter("minishell: \'",
				filename, "\': Permission denied\n", STDERR_FILENO), 1);
	else if (tempfd == -1)
	{
		shft_putter("minishell: \'", filename,
			"\': No such file or directory\n", STDERR_FILENO);
		word_clean(cmd, ft_strlen(cmd));
		return (1);
	}
	return (0);
}

int	shft_redir_inpt(char *cmd, t_shell_stuff *sh)
{
	char	*filename;
	int		tempfd;

	(void)sh;
	filename = shft_get_word(cmd + 1, '\0');
	tempfd = open(filename, O_RDONLY);
	clean_stuff(cmd, ft_strlen(filename));
	if (redir_test_access(filename, tempfd, cmd))
		return (free(filename), 1);
	free(filename);
	close(STDIN_FILENO);
	dup2(tempfd, STDIN_FILENO);
	return (0);
}

int	manage_redir_o(char *filename, int tempfd, char *p, int append)
{
	if (append)
		*p = -1;
	clean_stuff(p + append, ft_strlen(filename));
	if (access(filename, W_OK) == -1 && access(filename, F_OK) != -1)
	{
		shft_putter("minishell: \'", filename,
			"\': Permission denied\n", STDERR_FILENO);
		return (1);
	}
	close(STDOUT_FILENO);
	dup2(tempfd, STDOUT_FILENO);
	return (0);
}

int	shft_redir_outpt(char *cmd, t_shell_stuff *sh)
{
	char	*filename;
	int		tempfd;
	char	append;

	(void)sh;
	append = 0;
	if (cmd[1] == '>')
		append = 1;
	filename = shft_get_word(cmd + 1 + append, '\0');
	if (append)
		tempfd = open(filename, 02101, 0666);
	else
		tempfd = open(filename, 01101, 0666);
	if (append)
		*cmd = -1;
	if (manage_redir_o(filename, tempfd, cmd, append))
		return (free(filename), 1);
	return (free(filename), 0);
}
