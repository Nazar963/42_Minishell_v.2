/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_checker_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:21:41 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/28 21:16:19 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_cmd(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = NULL;
	new_str = (char *)ft_calloc(ft_strlen(str), sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
			i++;
		new_str[j++] = str[i++];
	}
	free(str);
	return (new_str);
}

int	execution_proccess_and_bonus(int *pp, t_shell_stuff *sh, int doset)
{
	char	**cmds;

	cmds = ft_split_operators(loco()->piece);
	if (cmds[0][0] == '1')
		return (ft_free_tab(cmds), sh->lststatus);
	else if (cmds[0][0] == '0')
	{
		loco()->counter = 1;
		if (execution_bonus_helper(cmds, pp, sh, doset) == 69)
			return (sh->lststatus);
	}
	else
		cmds = execution_and_bonus_helper_1(doset, cmds, sh, pp);
	ft_free_tab(cmds);
	return (sh->lststatus);
}

int	execution_proccess_or_bonus(int *pp, t_shell_stuff *sh, int doset)
{
	char	**cmds;

	cmds = ft_split_operators(loco()->piece);
	if (cmds[0][0] == '0')
		return (ft_free_tab(cmds), sh->lststatus);
	else if (cmds[0][0] == '1')
	{
		loco()->counter = 1;
		if (execution_bonus_helper(cmds, pp, sh, doset) == 69)
			return (sh->lststatus);
	}
	else
		cmds = execution_or_bonus_helper_1(doset, cmds, sh, pp);
	ft_free_tab(cmds);
	return (sh->lststatus);
}

char	*command_cleaner_and(char *tmp)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (tmp[i] && (shft_istab(tmp[i]) || tmp[i] == '&'))
		i++;
	new = ft_calloc(ft_strlen(tmp) - i + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (tmp[i])
	{
		new[j] = tmp[i];
		j++;
		i++;
	}
	free(tmp);
	return (new);
}

void	check_for_operator(char *cmd)
{
	int		i;
	char	fs;

	i = -1;
	fs = 0;
	if (!cmd || !*cmd)
		return ;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && fs != 2)
			fs ^= 1;
		if (cmd[i] == '\"' && fs != 1)
			fs ^= 2;
		if (fs)
			continue ;
		if (cmd[i] == '&' && cmd[i + 1] == '&')
			loco()->and = 1;
		else if (cmd[i] == '|' && cmd[i + 1] == '|')
			loco()->or = 1;
	}
	return ;
}
