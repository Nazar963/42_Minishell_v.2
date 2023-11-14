/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:45:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/14 18:34:37 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	shft_init_two_vars(int *a, int va, int *b, int vb)
{
	*a = va;
	*b = vb;
	return ;
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

char	*word_dup(char const *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((finish - start + 10), sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	**split;

	split = ft_calloc((count_words(s, c) + 20), sizeof(char *));
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
		if (ft_strlen(s) == 1 && s[0] == '*')
		{
			split[j++] = word_dup(s, 0, 1);
			break ;
		}
		i++;
	}
	return (split);
}

char	*ft_strchr_1(const char *s, char c)
{
	int	i;

	if (!s)
		return (malloc(1));
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (malloc(1));
}
