/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:23:14 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/01 23:52:03 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	surpass_q_dq(char *s, int *x)
{
	char	fs;

	fs = 0;
	while (shft_istab(s[(*x)]))
		(*x)++;
	while (s[(*x)])
	{
		if (s[(*x)] == '\'' && fs != 2)
			fs = 1;
		if (s[(*x)] == '\"' && fs != 1)
			fs = 2;
		if (!fs)
		{
			if (s[(*x)] == '&' && s[(*x) + 1] == '&')
				break ;
			else if (s[(*x)] == '|' && s[(*x) + 1] == '|')
				break ;
		}
		(*x)++;
	}
}

char	**control_copy(char **split, char *s, int *i, int *j)
{
	int	y;

	y = 0;
	while (s[(*i)])
	{
		if (s[(*i)] == '\'')
		{
			split[(*j)][y++] = s[(*i)++];
			while (s[(*i)] != '\'')
				split[(*j)][y++] = s[(*i)++];
		}
		if (s[(*i)] == '"')
		{
			split[(*j)][y++] = s[(*i)++];
			while (s[(*i)] != '"')
				split[(*j)][y++] = s[(*i)++];
		}
		if (s[(*i)] == '&' && s[(*i) + 1] == '&')
			break ;
		else if (s[(*i)] == '|' && s[(*i) + 1] == '|')
			break ;
		split[(*j)][y++] = s[(*i)++];
	}
	return (split);
}

char	**clean_control_copy(int *i, char **split, char *s, int *j)
{
	while (shft_istab(s[(*i)]))
		(*i)++;
	split = control_copy(split, s, i, j);
	while (s[(*i)] == '&' || s[(*i)] == '|')
		(*i)++;
	return (split);
}

char	**ft_split_operators(char *s)
{
	int		i;
	int		j;
	int		x;
	char	**split;

	loco()->pasta = 0;
	split = (char **)ft_calloc(3, sizeof(char *));
	if (!s || !split)
		return (0);
	shft_init_two_vars(&i, 0, &j, 0);
	while (++loco()->pasta <= 2)
	{
		x = i;
		surpass_q_dq(s, &x);
		split[j] = (char *)ft_calloc(x + 1, sizeof(char));
		x = 0;
		split = clean_control_copy(&i, split, s, &j);
		j++;
	}
	return (split);
}
