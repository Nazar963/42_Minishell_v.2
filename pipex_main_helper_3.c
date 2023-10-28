/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_helper_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:25:28 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/28 18:37:18 by lpollini         ###   ########.fr       */
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
	int	filefd;

	filefd = open(FILENAME2, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (!mode)
		dup2(filefd, STDOUT_FILENO);
	loco()->fd_setafter = open(FILENAME1, O_RDONLY);
}

int	shft_redirections(char **cmd, t_shell_stuff *sh, int *doset)
{
	if (shft_redir_inpt(*cmd, sh) || shft_redir_outpt(*cmd, sh, doset))
		return (sh->lststatus = 1, 1);
	if (loco()->redir_n_pipe && doset)
		builtin_temp_creat_1(1);
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

int	builtin_cmds(char *cd, t_shell_stuff *sh, int doset)
{
	int	res;

	if (doset && !loco()->fd_setafter)
		builtin_temp_creat(0);
	shft_after_setter();
	res = 0x7fffffff;
	if (!shft_strcmp_noend2(cd, "echo"))
		res = shft_cmd_echo(cd, sh);
	if (!shft_strcmp_noend2(cd, "export"))
		res = shft_cmd_export(cd, sh);
	shft_last_parse_1(&cd);
	if (!shft_strcmp_noend2(cd, "pwd"))
		res = shft_cmd_pwd(cd, sh);
	if (!shft_strcmp_noend2(cd, "env"))
		res = shft_cmd_env(cd, sh);
	if (!shft_strcmp_noend2(cd, "exit"))
		res = shft_cmd_exit(cd, sh);
	if (!shft_strcmp_noend2(cd, "cd"))
		res = shft_cmd_cd(cd, sh);
	if (!shft_strcmp_noend2(cd, "unset"))
		res = shft_cmd_unset(cd, sh);
	if (res == 0x7fffffff)
		ft_putstr_fd("Error: make better cmd check lol\n", STDERR_FILENO);
	return (res);
}
