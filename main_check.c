/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:19:06 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/10 19:33:39 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	fs_check(char fs, char a)
{
	if (a == '\'' && fs != 2)
		return (1);
	if (a == '\"' && fs != 1)
		return (2);
	return (0);
}

int	shft_ch_one(char **cmd, char *st, int ct)
{
	char	*temp;

	temp = *cmd;
	if ((temp[0] == '&' && temp[1] == '&') || (temp[0] == \
			'|' && temp[1] == '|'))
	{
		*st = 1;
		temp++;
	}
	else if (temp[0] == '(')
		*st = 3 + ct++ *(0);
	else if (temp[0] == ')')
		*st = 4 + ct-- *(0);
	else
		*st = 0;
	*cmd = temp;
	return (ct);
}

int	shft_ch_two(char st, char lst, int ct)
{
	if ((st == 0) && (lst == 4))
		return (1);
	if ((st == 1 || st == 4 || st == 3) && ((lst == 0 || lst \
				== 4) ^ (st != 3)))
		return (1);
	if (ct < 0)
		return (1);
	return (0);
}

int	shft_ch_checkok(char *cmd, t_shell_stuff *sh)
{
	char	st;
	char	lst;
	int		fs;
	int		ct;

	shft_init_two_vars(&fs, 0, &ct, 0);
	lst = -1;
	st = 0;
	while (*cmd)
	{
		while (shft_istab(cmd[0]) && cmd[1])
			cmd++;
		fs ^= fs_check(fs, *cmd);
		if (!fs)
		{
			ct = shft_ch_one(&cmd, &st, ct);
			if (shft_ch_two(st, lst, ct))
				return (sh->lststatus = 2, ft_putstr_fd(SYNTERR, ERRSTD) * 0);
			lst = st;
		}
		cmd++;
	}
	if (((st == 3 || st == 1) && !fs) || ct < 0)
		return (sh->lststatus = 2, ft_putstr_fd(SYNTERR, STDERR_FILENO) * 0);
	return (1);
}

char	shft_redir_syntax_ok(char *cmd, t_shell_stuff *sh)
{
	char	*t;

	t = shft_strrchr(cmd, '>', '\'', '\"');
	if ((t++))
	{
		if (*t == '>')
			t++;
		while (shft_istab(*t))
			t++;
		if (!*t || *t == '>' || *t == '<')
			return (sh->lststatus = 2, 1);
	}
	t = shft_strrchr(cmd, '<', '\'', '\"');
	if ((t++))
	{
		if (*t == '<')
			t++;
		while (shft_istab(*t))
			t++;
		if (!*t || *t == '<' || *t == '>')
			return (sh->lststatus = 2, 1);
	}
	return (0);
}
