/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shft_cmds_echo_exit_env_helper.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:27:05 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/24 17:02:51 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shft_cmd_env(char *cmd, t_shell_stuff *sh)
{
	int	i;

	if (BLTINS)
		printf("ENV BUILTIN\n");
	cmd += 3;
	while (shft_istab(*cmd))
		cmd++;
	if (*cmd)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return (127);
	}
	i = -1;
	while (++i <= sh->envn)
		if (sh->envp[i][0] && sh->envp[i][0] != '#')
			if (ft_strchr(sh->envp[i], '='))
				printf("%s\n", sh->envp[i]);
	return (0);
}
