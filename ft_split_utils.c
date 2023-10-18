/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:49:05 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/17 17:51:05 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_passer(char *str, int *index, int *count)
{
	if (str[*index] == '\'')
	{
		(*count)++;
		while (str[++(*index)] != '\'')
			(*count)++;
	}
	if (str[*index] == '"')
	{
		(*count)++;
		while (str[++(*index)] != '"')
			(*count)++;
	}
}

int	count_words_bonus(char *str)
{
	int	i;
	int	j;
	int	loco;

	i = 0;
	j = 0;
	loco = 0;
	while (str[j])
	{
		quotes_passer(str, &j, &i);
		if ((str[j] == '&' && str[j + 1] == '&')
			|| (str[j] == '|' && str[j + 1] == '|'))
		{
			if (loco == 1)
				break ;
			loco = 1;
			j++;
			i++;
		}
		i++;
		j++;
	}
	return (i);
}

char	*word_dup_bonus(char const *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((finish - start + 1), 8);
	if (start != 0 && shft_istab(str[start]))
		start++;
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	word[i + 1] = '\0';
	return (word);
}

char	**ft_split1(char const *s, char c, char ig)
{
	int		i;
	int		j;
	int		index;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	shft_init_two_vars(&i, 0, &j, 0);
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if (((s[i] == c && i > 0 && s[i - 1] != ig) || \
					i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

char	*ft_split_bonus(char *s, int *index)
{
	int		i;
	int		j;
	char	*split;

	*index = count_words_bonus(s);
	split = (char *)ft_calloc((*index + 1), sizeof(char));
	if (!s || !split)
		return (0);
	shft_init_two_vars(&i, 0, &j, 0);
	split = word_dup_bonus(s, 0, *index);
	split[*index + 1] = '\0';
	return (split);
}

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
			while (s[++(*i)] != '"')
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