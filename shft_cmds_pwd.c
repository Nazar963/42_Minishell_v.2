/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shft_cmds_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:34:40 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/24 19:34:10 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shft_istab(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	shft_cmd_pwd(char *cmd, t_shell_stuff *sh)
{
	(void)cmd;
	if (BLTINS)
		printf("PWD BUILTIN\n");
	printf("%s\n", shft_getenv("PWD", sh->envp, sh));
	return (0);
}

void	shft_ft_tp_hleper_1_0(void)
{
	if (loco()->parentheses != 1 && (loco()->g_and == 1 || loco()->g_or == 1))
	{
		loco()->g_and = 0;
		loco()->g_or = 0;
	}
	else if (loco()->parentheses != 1)
	{
		loco()->g_and = loco()->and;
		loco()->g_or = loco()->or;
	}
	loco()->and = 0;
	loco()->or = 0;
	loco()->out_to_pipe = 0;
	loco()->parentheses = 0;
}

void	shft_ft_tp_hleper_1_1(char *temp)
{
	loco()->piece = temp;
	loco()->and = 0;
	loco()->or = 0;
	pare()->controll = 0;
	pare()->first = 0;
	pare()->last = 0;
	check_for_operator(loco()->piece);
}
