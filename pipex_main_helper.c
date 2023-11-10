/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:23:25 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/10 18:58:44 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tb)
{
	int	i;

	i = 0;
	while (tb[i])
		free(tb[i++]);
	free(tb);
}

void	pipeft_exit(int arg)
{
	if (!(arg == WELLDONE))
	{
		write(2, "Error: ", 8);
		if (arg == PIPECREATERR)
			write(2, "Error during pipe creation!\n", 29);
		if (arg == NOINFILE)
			write(2, "Cannot find inpt!\n", 19);
		if (arg == NEOUGHINPT)
			write(2, "Invalid input!\n", 16);
		if (arg == ALLSENT)
			write(2, "Content was sent!\n", 19);
		if (arg == ALLRECIEVED)
			write(2, "Content was recieved!\n", 23);
		if (arg == NOOUTF)
			write(2, "Cant find out file!\n", 21);
		if (arg == CMDNOTFOUND)
			write(2, "Command not found!\n", 20);
		exit(127);
	}
	exit(0);
	return ;
}

char	*search_path(char *name, t_shell_stuff *sh)
{
	char	**temp;
	char	*otemp[2];
	int		i;

	i = 0;
	if (!name || !*name)
		return (NULL);
	temp = ft_split(shft_getenv("PATH", sh->envp, sh), ':');
	otemp[1] = ft_strjoin("/", name);
	while (temp[i])
	{
		otemp[0] = ft_strjoin(temp[i], otemp[1]);
		if (open(otemp[0], 0) != -1)
			break ;
		free(otemp[0]);
		i++;
	}
	if (!temp[i])
		i = -1;
	ft_free_tab(temp);
	free(otemp[1]);
	if (i != -1)
		return (otemp[0]);
	return (NULL);
}

char	**shft_dupenv(t_shell_stuff *sh)
{
	char	**res;
	int		i;
	int		h;

	i = -1;
	h = 0;
	res = ft_calloc(sh->envn + 1, sizeof(char *) * 8);
	while (++i <= sh->envn)
		if (sh->envp[i][0] && sh->envp[i][0] != '#')
			res[h++] = ft_strdup(sh->envp[i]);
	res[h] = NULL;
	return (res);
}

int	shft_putter(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd_1(s2, fd);
	ft_putstr_fd(s3, fd);
	return (0);
}
