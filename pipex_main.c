/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:46:25 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/12 01:24:35 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*littel_better(char *s)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup(s);
	while (res[i])
		i++;
	while (i-- && shft_istab(res[i]))
		res[i] = '\0';
	return (res);
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

int	check_for_bonus(char *cmd)
{
	int		i;
	char	flag;
	char	fs;

	i = 0;
	flag = 0;
	fs = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && fs != 2)
			fs ^= 1;
		if (cmd[i] == '\"' && fs != 1)
			fs ^= 2;
		else if (!fs && ((cmd[i] == '&' && cmd[i + 1] == '&')
				|| (cmd[i] == '|' && cmd[i + 1] == '|')))
			flag = 1 + 0 * loco()->n++;
		i++;
	}
	if (flag)
		return (1);
	return (0);
}

int	shft_fr_to(char *cmd, t_shell_stuff *sh, int doset, int pipe)
{
	char	*tmp[2];
	int		pp[2];
	char	*temp;

	tmp[0] = ft_strdup(cmd);
	if (check_for_bonus(tmp[0]) == 1)
	{
		while (loco()->n-- > 0 && tmp[0])
		{
			if (loco()->flagc == 1)
				break ;
			temp = ft_split_bonus(tmp[0], &loco()->index);
			loco()->piece = temp;
			check_for_operator(loco()->piece);
			tmp[0] = shft_ft_tp_helper_1(&pp[0], sh, doset, tmp[0]);
			if (!tmp[0] || !tmp[0][0])
				return (free(tmp[0]), sh->lststatus);
		}
	}
	else
		tmp[0] = shft_ft_tp_helper_nobonus(pipe, sh, doset, tmp[0]);
	free(tmp[0]);
	if (tmp[0] != NULL)
		loco()->n = 0;
	return (sh->lststatus);
}

int	shft_wait_dudes(int pipes)
{
	int	i;
	int	lols[2];

	i = 0;
	lols[1] = 0;
	lols[0] = 0;
	while (i <= pipes)
	{
		waitpid(loco()->p[i], lols, 0);
		lols[0] = WEXITSTATUS(lols[0]);
		if (lols[0] != 0 && !lols[1])
			lols[1] = lols[0];
		i++;
	}
	return (lols[1]);
}

int	shft_pipexexec(char **cmds, int pipes, t_shell_stuff *sh)
{
	int			i;

	loco()->p = ft_calloc(pipes + 1, sizeof(t_pipeline));
	i = 0;
	if (pipes)
		i = shft_fr_to(cmds[i], sh, 1, i) * 0 + i + 1;
	else
		i = shft_fr_to(cmds[i], sh, 0, i) * 0 + i + 1;
	while (i < pipes && !loco()->sigstop)
		i = shft_fr_to(cmds[i], sh, 1, i) * 0 + i + 1;
	dup2(sh->tempfds[1], STDOUT_FILENO);
	if (i == pipes && !loco()->sigstop)
		i = shft_fr_to(cmds[i], sh, 0, i) * 0 + i + 1;
	dup2(sh->tempfds[0], STDIN_FILENO);
	dup2(sh->tempfds[1], STDOUT_FILENO);
	if (sh->doexit == -1)
		sh->lststatus = shft_wait_dudes(pipes);
	free(loco()->p);
	return (sh->lststatus);
}
