/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:30:22 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/10 09:42:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shft_isalnum(const int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

char	*ft_strtab_join_free(char **s)
{
	char	*res;
	char	*temp;

	res = ft_strdup("");
	while (*s)
	{
		temp = res;
		res = ft_strjoin(res, *s);
		free(*s);
		free(temp);
		s++;
	}
	return (res);
}

char	*shft_arg(t_shell_stuff *sh, char *str)
{
	int	temp;

	temp = shft_atoi(str);
	if (temp < sh->argn)
		return (ft_strdup(sh->args[temp]));
	while (shft_isalnum(*str))
		str++;
	return (ft_strdup(str));
}

int	shft_istab1(char *str)
{
	while (*str == '\'' || *str == '\"')
		str++;
	if (shft_istab(*str) || !*str)
		return (1);
	return (0);
}

/*checks case with only redirections and no command*/
char	last_exiter(char *cmd)
{
	char	fs;

	while (shft_istab(*cmd))
		cmd++;
	if (!*cmd)
		return (1);
	if (*cmd != '<' && *cmd != '>')
		return (0);
	cmd++;
	while (shft_istab(*cmd))
		cmd++;
	fs = 0;
	while ((!shft_istab(*cmd) || fs) && *cmd)
	{
		if (*cmd == '\'' && fs != 1)
			fs ^= 2;
		if (*cmd == '\"' && fs != 2)
			fs ^= 1;
		cmd++;
	}
	return (last_exiter(cmd));
}
