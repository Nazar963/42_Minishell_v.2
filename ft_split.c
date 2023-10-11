/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:45:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/11 11:53:33 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	shft_init_two_vars(int *a, int va, int *b, int vb)
{
	*a = va;
	*b = vb;
}

int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c && *(str + 1) != c)
			trigger = 0;
		str++;
	}
	return (i);
}

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

char	*word_dup(char const *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((finish - start + 1), 8);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	*word_dup_bonus(char const *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((finish - start + 1), 8);
	if (start != 0 && str[start] == ' ')
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

char	**ft_split(char const *s, char c)
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
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
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
	char	*tmp;

	*index = count_words_bonus(s);
	shft_init_two_vars(&i, 0, &j, 0);
	split = word_dup_bonus(s, 0, *index);
	split[*index + 1] = '\0';
	return (split);
}

void	surpass_q_dq(char *s, int *x)
{
	while (s[(*x)] == ' ')
		(*x)++;
	while (s[(*x)])
	{
		if (s[(*x)] == '\'')
			while (s[++(*x)] != '\'')
				;
		if (s[(*x)] == '"')
			while (s[++(*x)] != '"')
				;
		if (s[(*x)] == '&' && s[(*x) + 1] == '&')
			break ;
		else if (s[(*x)] == '|' && s[(*x) + 1] == '|')
			break ;
		(*x)++;
	}
}

char	**ft_split_operators(char *s)
{
	int				counter;
	t_vector4_int	vs;
	char			**split;
	char			*tmp;

	counter = 0;
	vs.y = 0;
	split = (char **)ft_calloc(3, sizeof(char *));
	if (!s || !split)
		return (0);
	shft_init_two_vars(&vs.i, 0, &vs.j, 0);
	while (++counter <= 2)
	{
		vs.x = vs.i;
		surpass_q_dq(s, &vs.x);
		split[vs.j] = (char *)ft_calloc(vs.x + 1, sizeof(char));
		vs.x = 0;
		while (s[vs.i] == ' ')
			vs.i++;
		while (s[vs.i])
		{
			if (s[vs.i] == '\'')
			{
				split[vs.j][vs.y++] = s[vs.i++];
				while (s[vs.i] != '\'')
					split[vs.j][vs.y++] = s[vs.i++];
			}
			if (s[vs.i] == '"')
			{
				split[vs.j][vs.y++] = s[vs.i++];
				while (s[++vs.i] != '"')
					split[vs.j][vs.y++] = s[vs.i++];
			}
			if (s[vs.i] == '&' && s[vs.i + 1] == '&')
				break ;
			else if (s[vs.i] == '|' && s[vs.i + 1] == '|')
				break ;
			split[vs.j][vs.y++] = s[vs.i++];
		}
		while (s[vs.i] == '&' || s[vs.i] == '|')
			vs.i++;
		vs.j++;
		vs.y = 0;
	}
	return (split);
}
