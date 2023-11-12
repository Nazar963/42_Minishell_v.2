/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_helper_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:25:28 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/12 11:08:02 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shft_last_parse_1(char **s)
{
	char	*ori;

	ori = *s;
	while (*ori)
	{
		if (*ori == -1)
			*ori = '>';
		if (*ori == -2)
			*ori = '<';
		ori++;
	}
	word_clean(*s, ft_strlen(*s));
	return ;
}

char	shft_redirector(t_shell_stuff *sh, char *cmd)
{
	char	fs;

	fs = 0;
	while (*cmd && ((*cmd != '<' && *cmd != '>') || fs))
		fs ^= fs_check(fs, *(cmd++));
	if (!*cmd || cmd[1] == '<')
		return (0);
	if (*cmd == '<' && shft_redir_inpt(cmd, sh))
		return (1);
	if (*cmd == '>' && shft_redir_outpt(cmd, sh))
		return (1);
	cmd++;
	return (shft_redirector(sh, cmd));
}

int	shft_redirections(char **cmd, t_shell_stuff *sh)
{
	if (shft_redir_syntax_ok(*cmd, sh))
		return (ft_putstr_fd("minishell: syntax error\n", ERRSTD), 1);
	if (shft_redirector(sh, *cmd))
		return (sh->lststatus = 1, 1);
	word_clean(*cmd, ft_strlen(*cmd));
	if (loco()->limiter_flag == -1)
		return (1);
	shft_last_parse_1(cmd);
	return (0);
}

int	shft_is_builtin(char *cd)
{
	if (shft_strcmp_noend2(cd, "pwd") && shft_strcmp_noend2(cd, "env") && \
		shft_strcmp_noend2(cd, "echo") && shft_strcmp_noend2(cd, "exit") && \
		shft_strcmp_noend2(cd, "cd") && shft_strcmp_noend2(cd, "unset") && \
		shft_strcmp_noend2(cd, "export"))
		return (-1);
	return (0);
}

void	non_executable_handler(char *cmd, t_shell_stuff *sh)
{
	char	*temp;

	if (sh->lststatus == 126)
		return ;
	sh->lststatus = 127;
	temp = littel_better(cmd);
	if (shft_strchr(cmd, '/', '\'', '\"') && access(cmd, F_OK) == -1)
		shft_putter("minishell: \'", temp,
			"\': No such file or directory\n", STDERR_FILENO);
	else
		shft_putter("minishell: \'", temp,
			"\': command not found\n", STDERR_FILENO);
	sh->lststatus = 127;
	free(temp);
	return ;
}
