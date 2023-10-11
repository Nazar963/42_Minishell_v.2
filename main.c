/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:32:51 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/11 14:13:00 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handle(int a)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (!loco()->sigpass)
		rl_redisplay();
	loco()->sigpass = a;
}

void	shft_init(t_shell_stuff *sh, char *args[], char *envp[], int argn)
{
	sh->tempfds[1] = dup(STDOUT_FILENO);
	sh->tempfds[0] = dup(STDIN_FILENO);
	signal(SIGINT, &sigint_handle);
	signal(SIGQUIT, &sigint_handle);
	sh->lststatus = 0;
	sh->usr = getenv("USER");
	if (!sh->usr)
		sh->usr = ft_calloc(1, 8);
	sh->envn = shft_env_init_free(sh->envp, envp, 0);
	sh->args = args;
	sh->argn = argn;
	sh->pwd = ft_strdup(getenv("PWD"));
	if (!sh->pwd || access(sh->pwd, F_OK) == -1)
		sh->pwd = ft_strdup("/");
	update_env_free(sh->envp, sh->pwd, sh);
	sh->doexit = -1;
	sh->exit_code = 0;
	loco()->sigpass = 0;
}

int	shft_exit(int e, t_shell_stuff *sh)
{
	shft_prompt(sh, 1);
	sh->envn = shft_env_init_free(sh->envp, NULL, 1);
	shft_cmd_cd(NULL, sh);
	free(sh->pwd);
	rl_clear_history();
	exit(sh->exit_code);
}

//* ------------- a way to have a struct by calling a function ------------- */

t_loco	*loco(void)
{
	static t_loco	loco = {NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0};

	return (&loco);
}

char	fs_check(char fs, char a)
{
	if (a == '\'' && fs != 2)
		return (1);
	if (a == '\"' && fs != 1)
		return (2);
	return (fs);
}

int	shft_ch_checkok(char *cmd)
{
	char	st;
	char	lst;
	char	fs;
	int		ct;

	fs = 0;
	ct = 0;
	lst = -1;
	st = 0;
	while (*cmd)
	{
		fs = fs_check(fs, *cmd);
		if (!fs)
		{
			while (shft_istab(*cmd) && cmd[1])
				cmd++;
			if ((cmd[0] == '&' && cmd[1] == '&') || (cmd[0] == \
					'|' && cmd[1] == '|'))
				st = 1 + *(cmd++) *(0);
			else if (cmd[0] == '(')
				st = 3 + ct++ *(0);
			else if (cmd[0] == ')')
				st = 4 + ct-- *(0);
			else
				st = 0;
			while (shft_istab(*cmd) && cmd[1])
				cmd++;
			if ((st == 0) && (lst == 4))
				return (ft_putstr_fd(ERRSYNTAX, STDERR_FILENO) * 0);
			if ((st == 1 || st == 4 || st == 3) && ((lst == 0 || lst \
						== 4) ^ (st != 3)))
				return (ft_putstr_fd(ERRSYNTAX, STDERR_FILENO) * 0);
			if (ct < 0)
				return (ft_putstr_fd(ERRSYNTAX, STDERR_FILENO) * 0);
			lst = st;
		}
		cmd++;
	}
	if (((st == 3 || st == 1) && !fs) || ct < 0)
		return (ft_putstr_fd(ERRSYNTAX, STDERR_FILENO) * 0);
	return (1);
}

int	main(int argn, char *args[], char *envp[])
{
	t_shell_stuff	shell;
	char			*cmd_buff;

	shft_init(&shell, args, envp, argn);
	while (shell.doexit == -1)
	{
		cmd_buff = shft_prompt(&shell, 0);
		loco()->sigpass = 1;
		loco()->exit = 0;
		if (cmd_buff && *cmd_buff)
			add_history(cmd_buff);
		if (cmd_buff)
		{
			if (!shft_ch_checkok(cmd_buff))
				continue ;
			shft_execute_cmd(&shell, cmd_buff);
			free(cmd_buff);
		}
		else
		{
			write(1, "exit\n", 5);
			break ;
		}
		update_env_free(shell.envp, shell.pwd, &shell);
		loco()->sigpass = 0;
	}
	shft_exit(-1, &shell);
}
