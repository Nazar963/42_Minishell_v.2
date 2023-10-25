/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:33:19 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/25 16:57:16 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_put(t_shell_stuff *sh)
{
	char	*put;

	put = ft_strdup(GREENBOLD);
	put = ft_strjoin_free(put, sh->usr);
	put = ft_strjoin_free(put, "@");
	put = ft_strjoin_free(put, PROMPT);
	put = ft_strjoin_free(put, UNSET);
	put = ft_strjoin_free(put, ":");
	put = ft_strjoin_free(put, BLUEBOLD);
	return (put);
}

char	*better_pwd(char *pwd, const char *usr)
{
	char	*res;

	res = ft_strnstr(pwd, usr, ft_strlen(pwd));
	if (!res)
		return (ft_strdup(pwd));
	res = ft_strjoin("~", res + ft_strlen(usr));
	return (res);
}

char	*shft_prompt(t_shell_stuff *sh, int dofree)
{
	static char	*put;
	char		*tmp[2];

	if (dofree)
	{
		if (put)
			free(put);
		put = NULL;
		return (NULL);
	}
	if (!put)
		put = build_put(sh);
	tmp[1] = ft_strdup(put);
	tmp[0] = ft_strjoin_free_1(tmp[1], better_pwd(sh->pwd, sh->usr));
	free(tmp[1]);
	tmp[0] = ft_strjoin_free(tmp[0], UNSET);
	tmp[0] = ft_strjoin_free(tmp[0], "$ ");
	tmp[1] = readline(tmp[0]);
	free(tmp[0]);
	return (tmp[1]);
}

int	export_lol(t_shell_stuff *sh)
{
	int		tempfds[2];
	int		i;
	int		filefd;

	tempfds[1] = dup(STDIN_FILENO);
	i = 0;
	filefd = open(".tempfile1", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	while (i <= sh->envn)
	{
		if (sh->envp[i][0] && sh->envp[i][0] != '#')
		{
			ft_putstr_fd("declare -x ", filefd);
			ft_putstr_fd(sh->envp[i], filefd);
			ft_putstr_fd("\n", filefd);
		}
		i++;
	}
	shft_execute_cmd(sh, "/usr/bin/sort .tempfile1");
	shft_execute_cmd(sh, "/usr/bin/rm .tempfile1");
	dup2(tempfds[1], STDIN_FILENO);
	return (0);
}

char	*ft_strdup_clean(char *s)
{
	char	*res;
	int		iter;
	char	t;

	iter = 0;
	t = 0;
	res = malloc(ft_strlen(s) + 1);
	while (*s)
	{
		if (*s == t)
			t = 0;
		if ((*s == '\'' || *s == '\"') && !t)
			t = *s;
		else
			res[iter++] = *s;
		s++;
	}
	res[iter] = '\0';
	return (res);
}
