/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:45:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/10 18:59:28 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shft_split1_test_1(char *s, char ig1, char ig2, int test)
{
	if (s[0] == ig1 && test != 2)
	{
		test ^= 1;
		s[0] = -1;
	}
	if (s[0] == ig2 && test != 1)
	{
		test ^= 2;
		s[0] = -1;
	}
	return (test);
}

char	*word_dup_1(char const *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((finish - start + 1), 8);
	while (start < finish)
	{
		if (str[start] != -1)
			word[i++] = str[start];
		start++;
	}
	word[i] = '\0';
	return (word);
}

int	count_words_1(const char *str, char c)
{
	int		i;
	int		trigger;
	char	fs;

	i = 0;
	fs = 0;
	trigger = 0;
	while (*str)
	{
		if (str[0] == '\'' && fs != 2)
			fs ^= 1;
		if (str[0] == '\"' && fs != 1)
			fs ^= 2;
		else if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c && *(str + 1) != c && !fs)
			trigger = 0;
		str++;
	}
	return (i);
}

char	**shft_split2(char *s, char c, char ig1, char ig2)
{
	int		i;
	int		j;
	int		index;
	char	**split;
	int		test;

	split = ft_calloc((count_words_1(s, c) + 2), 8);
	if (!s || !split)
		return (0);
	shft_init_two_vars(&i, 0, &j, 0);
	shft_init_two_vars(&test, 0, &index, -1);
	while (i <= ft_strlen(s))
	{
		test = shft_split1_test_1((char *)s + i, ig1, ig2, test);
		if (s[i] != c && index < 0)
			index = i;
		else if (((s[i] == c && !test) || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup_1(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
