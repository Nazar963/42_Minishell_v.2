/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shft_cmds_export_unset.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:34:40 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/25 17:56:36 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shft_cmd_unset_1(char *cmd, t_shell_stuff *sh, char ct)
{
	char	*temp;
	int		line;

	if (shft_strchr(cmd, ' ', '\'', '\"'))
	{
		temp = ft_strjoin("unset", shft_strchr(cmd, ' ', '\'', '\"'));
		shft_cmd_unset(temp, sh);
		free(temp);
	}
	temp = shft_strchr(cmd, ' ', '\'', '\"');
	if (temp)
	{
		ct = temp[0];
		temp[0] = '\0';
	}
	line = shft_getenv_line(cmd, sh->envp, sh);
	if (temp)
		temp[0] = ct;
	return (line);
}

/* UNSET builtin */
int	shft_cmd_unset(char *cmd, t_shell_stuff *sh)
{
	int		line;
	char	ct;

	ct = 0;
	if (BLTINS)
		printf("UNSET BUILTIN\n");
	cmd += 5;
	while (shft_istab(*cmd))
		cmd++;
	if (ft_strchr(cmd, '='))
		*ft_strchr(cmd, '=') = '\0';
	line = shft_cmd_unset_1(cmd, sh, ct);
	if (line > 0)
	{
		free(sh->envp[line]);
		sh->envp[line] = ft_strdup("###");
	}
	return (0);
}

int	ft_ischar(char a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	return (0);
}

int	export_ok(char *s, t_shell_stuff *sh)
{
	char	*temp;
	int		t;

	t = 0;
	if (!ft_ischar(*s))
		t = ft_putstr_fd(ERRBADASS, STDERR_FILENO) * 0 + 1;
	while (*s && *s != '=' && !shft_istab(*s))
		if (!ft_isalnum(*(s++)) && !t)
			t = ft_putstr_fd(ERRBADASS, STDERR_FILENO) * 0 + 1;
	temp = shft_strchr(s, ' ', '\"', '\'');
	if (temp)
	{
		while (shft_istab(*temp))
			temp++;
		if (*temp)
		{
			temp[-1] = '\0';
			temp = ft_strjoin("export ", temp);
			shft_cmd_export(temp, sh);
			free(temp);
		}
	}
	if (t)
		return (1);
	return (0);
}

//* EXPORT builtin*/
int	shft_cmd_export(char *cmd, t_shell_stuff *sh)
{
	char	*temp[2];

	cmd += 6;
	while (shft_istab(*cmd))
		cmd++;
	if (BLTINS)
		printf("EXPORT BUILTIN\n");
	if (!*cmd)
		return (export_lol(sh));
	if (export_ok(cmd, sh))
		return (sh->lststatus = 1, 1);
	temp[0] = ft_strjoin("unset ", cmd);
	shft_cmd_unset(temp[0], sh);
	free(temp[0]);
	sh->envn++;
	temp[1] = sh->envp[sh->envn];
	sh->envp[sh->envn] = ft_strdup_clean(cmd);
	free(temp[1]);
	return (sh->lststatus);
}
