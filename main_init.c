/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:18:03 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/19 13:19:46 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*creat_prompt(t_shell_stuff *shell, char *cmd_buff)
{
	cmd_buff = shft_prompt(shell, 0);
	loco()->sigpass = 1;
	loco()->exit = 0;
	return (cmd_buff);
}

t_loco	*loco(void)
{
	static t_loco	loco = {NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		NULL, NULL, 0, 0, 0, 0, 0, 0, 0};

	return (&loco);
}

void	reset_loco(void)
{
	*(loco()) = (t_loco){NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		NULL, NULL, 0, 0, 0, 0, 0, 0, 0};
}
