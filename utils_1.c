/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:46:55 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/12 13:11:18 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	piperlol(int *pp)
{
	pipe(pp);
	close(*(pp + 1));
	dup2(*pp, STDIN_FILENO);
	return ;
}

void	clean_stuff(char *s, int l)
{
	while (*s == '<' || *s == '>')
		*(s++) = -1;
	while (shft_istab(*s) || *s == '\'' || *s == '\"')
		*(s++) = -1;
	while ((*s == '\'' || *s == '\"' || l--) && *s)
		*(s++) = -1;
	return ;
}

int	builtin_cmds(char *cd, t_shell_stuff *sh, int doset)
{
	int	res;

	close(STDIN_FILENO);
	if (doset)
		tempfile_creat();
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
	loco()->lastcng = 1;
	return (res);
}

char	*shft_very_lol(void)
{
	char	*res;

	res = check_for_wildcard_normal(loco()->piece);
	loco()->piece = res;
	pare()->flag = loco()->n;
	return (res);
}

void	read_stdin_1( void )
{
	char	*buff;

	loco()->limiter_flag = -1;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buff = readline("> ");
		if (!buff || !ft_strcmp(buff, pare()->extra_2))
			break ;
		ft_putstr_fd(buff, pare()->child_fd);
		ft_putstr_fd("\n", pare()->child_fd);
		free(buff);
	}
	if (!buff)
		shft_putter(LIMITERMSG, pare()->extra_2, "\')\n", STDERR_FILENO);
	close(pare()->child_fd);
	free(pare()->extra_2);
	free(buff);
	return ;
}
