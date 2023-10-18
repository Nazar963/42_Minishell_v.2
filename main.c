/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:32:51 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/18 18:21:37 by naal-jen         ###   ########.fr       */
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

int	shft_exit(t_shell_stuff *sh)
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
	static t_loco	loco = {NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		NULL, NULL, 0, 0, 0, 0, 0, 0, 0};

	return (&loco);
}

void	reset_loco()
{
	*(loco()) = (t_loco){NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		NULL, NULL, 0, 0, 0, 0, 0, 0, 0};
}

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

char	*final_check(char *str)
{
	int		i;
	int		j;
	int		counter;
	char	*new_str;

	i = 0;
	j = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '(')
			counter++;
		else if (str[i] == ')')
			counter--;
		i++;
	}
	i = 0;
	if (counter)
	{
		new_str = ft_calloc(ft_strlen(str) + 1 - counter, sizeof(char));
		while (str[i])
		{
			if (str[i] == '(' ||str[i] == ')')
			{
				i++;
				continue ;
			}
			new_str[j] = str[i];
			i++;
			j++;
		}
		free(str);
		return (new_str);
	}
	return (str);
}

char	*check_for_right_parenthesis(char *s)
{
	int		i;
	int		open_pare;
	int		close_pare;
	int		double_first;
	char	*new_str;

	i = 0;
	open_pare = 0;
	close_pare = 0;
	double_first = 0;
	while (s[i])
	{
		if (s[i] == '(' && s[i + 1] == '(')
		{
			if (i == 0)
				double_first = 1;
			open_pare = i;
		}
		if (s[i] == ')' && s[i + 1] == ')')
		{
			close_pare = 1;
			break ;
		}
		i++;
	}
	if ((open_pare && close_pare) || (double_first && close_pare))
	{
		new_str = ft_strdup_len(s, open_pare - 1);
		new_str = final_check(new_str);
		return (new_str);
	}
	return (NULL);
}

char	*better_parenthesis(char *s)
{
	char	*res;
	int		i;
	int		j;
	char	fs;

	i = 0;
	j = 0;
	fs = 0;
	res = NULL;
	res = check_for_right_parenthesis(s);
	if (res)
	{
		free(s);
		return (res);
	}
	res = malloc(ft_strlen(s) * 2 + 1);
	while (s[i])
	{
		if (s[i] == '\'' && fs != 2)
			fs = 1;
		if (s[i] == '\"' && fs != 1)
			fs = 2;
		res[j++] = s[i];
		if (!fs && (s[i] == '(' || s[i] == ')'))
			res[j++] = ' ';
		i++;
	}
	res[j] = '\0';
	free(s);
	return (res);
}

int	shft_ch_checkok(char *cmd)
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
				return (ft_putstr_fd(ERRSYNTAX, STDERR_FILENO) * 0);
			lst = st;
		}
		cmd++;
	}
	if (((st == 3 || st == 1) && !fs) || ct < 0)
		return (ft_putstr_fd(ERRSYNTAX, STDERR_FILENO) * 0);
	return (1);
}

char	*creat_prompt(t_shell_stuff *shell, char *cmd_buff)
{
	cmd_buff = shft_prompt(shell, 0);
	loco()->sigpass = 1;
	loco()->exit = 0;
	return (cmd_buff);
}

int	main(int argn, char *args[], char *envp[])
{
	t_shell_stuff	shell;
	char			*cmd_buff;

	shft_init(&shell, args, envp, argn);
	while (shell.doexit == -1)
	{
		cmd_buff = creat_prompt(&shell, cmd_buff);
		if (cmd_buff && *cmd_buff)
			add_history(cmd_buff);
		if (cmd_buff)
		{
			if (!shft_ch_checkok(cmd_buff))
				continue ;
			cmd_buff = better_parenthesis(cmd_buff);

			// printf("@@@%s\n", cmd_parentheses_and_cleaner(cmd_buff,
			// 		2, 5, &shell));
					
			shft_execute_cmd(&shell, cmd_buff);
			free(cmd_buff);
			reset_loco();
		}
		else
		{
			write(1, "exit\n", 5);
			break ;
		}
		update_env_free(shell.envp, shell.pwd, &shell);
		loco()->sigpass = 0;
	}
	shft_exit(&shell);
}
