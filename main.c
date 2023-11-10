/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:32:51 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/10 18:48:47 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	limiter_case(int a)
{
	if (loco()->limiter_flag == -1)
	{
		close(pare()->child_fd);
		free(pare()->extra_2);
		exit(0);
	}
	if (a == SIGQUIT)
		return (1);
	kill(loco()->limiter_pid, SIGINT);
	waitpid(loco()->limiter_pid, NULL, 0);
	loco()->limiter_flag = -2;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	return (1);
}

void	sigint_handle(int a)
{
	loco()->flagc = 1;
	loco()->sigstop = 1;
	if ((loco()->limiter_flag == 1 || loco()->limiter_flag
			== -1) && limiter_case(a))
		return ;
	if (a == SIGQUIT && loco()->sigpass)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	if (loco()->sigpass)
		kill(loco()->forkpid, a);
	if (a == SIGQUIT)
		return ((void)rl_redisplay());
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (!loco()->sigpass)
		rl_redisplay();
	loco()->sigpass = 0;
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

int	shft_exit(t_shell_stuff *sh)
{
	shft_prompt(sh, 1);
	sh->envn = shft_env_init_free(sh->envp, NULL, 1);
	shft_cmd_cd(NULL, sh);
	free(sh->pwd);
	rl_clear_history();
	if (pare()->extra)
		read_stdin_1();
	exit(sh->exit_code);
}

int	main(int argn, char *args[], char *envp[])
{
	t_shell_stuff	shell;
	char			*cmd_buff;

	shft_init(&shell, args, envp, argn);
	while (shell.doexit == -1)
	{
		cmd_buff = creat_prompt(&shell, cmd_buff);
		signal(SIGQUIT, &sigint_handle);
		if (cmd_buff && *cmd_buff)
			add_history(cmd_buff);
		if (cmd_buff)
		{
			cmd_buff = better_parenthesis(cmd_buff);
			shft_execute_cmd(&shell, cmd_buff);
			free(cmd_buff);
			reset_loco();
		}
		else if (write(1, "exit\n", 5))
			break ;
		update_env_free(shell.envp, shell.pwd, &shell);
		loco()->sigpass = 0;
	}
	shft_exit(&shell);
}
