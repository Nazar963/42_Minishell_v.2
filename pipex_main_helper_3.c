/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_helper_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:25:28 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/09 21:32:43 by codespace        ###   ########.fr       */
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
}

void	builtin_temp_creat(char mode)
{
	int	filefd;

	filefd = open(FILENAME1, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (!mode)
		dup2(filefd, STDOUT_FILENO);
	filefd = open(FILENAME1, O_RDONLY);
	dup2(filefd, STDIN_FILENO);
}

void	builtin_temp_creat_1(char mode)
{
	int	boh;

	(void )mode;
	boh = open(FILENAME2, O_CREAT | O_RDONLY, 0666);
	loco()->fd_setafter = boh;
}

int	shft_redirections(char **cmd, t_shell_stuff *sh, int *doset)
{
	if (shft_redir_syntax_ok(*cmd, sh))
		return (ft_putstr_fd("minishell: syntax error\n", ERRSTD), 1);
	if (last_exiter(*cmd))
		return (sh->lststatus = 0, 1);
	if (shft_redir_inpt(*cmd, sh) || shft_redir_outpt(*cmd, sh, doset))
		return (sh->lststatus = 1, 1);
	if (loco()->redir_n_pipe && *doset)
		builtin_temp_creat_1(1);
	if (loco()->limiter_flag == -1)
		return (1);
	loco()->sigpass = 1;
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
