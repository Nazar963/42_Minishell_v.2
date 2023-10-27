/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_helper_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:25:08 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/27 23:55:47 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_stdin(char *limiter, t_shell_stuff *sh)
{
	char	*buff;
	int		pipefd[2];
	char	*comp;

	pipe(pipefd);
	if (!limiter_ok(&comp, limiter))
		return (1);
	while (1)
	{
		ft_putstr_fd("> ", sh->tempfds[1]);
		buff = get_next_line(sh->tempfds[0]);
		if (!buff || !ft_strcmp(buff, comp) || loco()->limiter_flag == -1)
			break ;
		ft_putstr_fd(buff, pipefd[1]);
		free(buff);
	}
	if (!buff)
		shft_putter(LIMITERMSG, comp, "\')\n", STDERR_FILENO);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	free(buff);
	limiter[0] = -1;
	clean_stuff(limiter + 1, ft_strlen(comp));
	free(comp);
	return (0);
}

int	redir_test_access(char *filename, int tempfd, char *cmd)
{
	if (access(filename, R_OK) == -1 && access(filename, F_OK) != -1)
		return (shft_putter("minishell: \'",
				filename, "\': Permission denied\n", STDERR_FILENO) + 1);
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
	char	*p;
	char	*filename;
	int		tempfd;

	p = shft_strchr(cmd, '<', '\'', '\"');
	if (!p)
		return (word_clean(cmd, ft_strlen(cmd)), 0);
	if (*(p + 1) == '<')
	{
		if (!read_stdin(p, sh))
			return (shft_redir_inpt(cmd, sh));
		else
			return (1);
	}
	filename = shft_get_word(p + 1, '\0');
	tempfd = open(filename, O_RDONLY);
	clean_stuff(p, ft_strlen(filename));
	if (redir_test_access(filename, tempfd, cmd))
	{
		free(filename);
		return (1);
	}
	free(filename);
	dup2(tempfd, STDIN_FILENO);
	return (shft_redir_inpt(cmd, sh));
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
	dup2(tempfd, STDOUT_FILENO);
	return (0);
}

int	shft_redir_outpt(char *cmd, t_shell_stuff *sh, int *doset)
{
	char	*p;
	char	*filename;
	int		tempfd;
	int		append;

	p = shft_strchr(cmd, '>', '\'', '\"');
	if (!p)
		return (word_clean(cmd, ft_strlen(cmd)), 0);
	*doset = 0;
	append = 0;
	if (*(p + 1) == '>')
		append = 1;
	filename = shft_get_word(p + 1 + append, '\0');
	if (append)
		tempfd = open(filename, 02101, 0666);
	else
		tempfd = open(filename, 01101, 0666);
	if (append)
		*p = -1;
	if (manage_redir_o(filename, tempfd, p, append))
		return (free(filename), 1);
	loco()->redir_n_pipe = 1;
	return (free(filename), shft_redir_outpt(cmd, sh, doset));
}
