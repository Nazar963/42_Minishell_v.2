/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:45:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/17 17:51:21 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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





// char	**ft_split_operators(char *s)
// {
// 	int		counter;
// 	int		i;
// 	int		j;
// 	int		y;
// 	int		x;
// 	char	**split;
// 	char	*tmp;

// 	counter = 0;
// 	y = 0;
// 	split = (char **)ft_calloc(3, sizeof(char *));
// 	if (!s || !split)
// 		return (0);
// 	shft_init_two_vars(&i, 0, &j, 0);
// 	while (++counter <= 2)
// 	{
// 		x = i;
// 		surpass_q_dq(s, &x);
// 		split[j] = (char *)ft_calloc(x + 1, sizeof(char));
// 		x = 0;
// 		while (s[i] == ' ')
// 			i++;
// 		while (s[i])
// 		{
// 			if (s[i] == '\'')
// 			{
// 				split[j][y++] = s[i++];
// 				while (s[i] != '\'')
// 					split[j][y++] = s[i++];
// 			}
// 			if (s[i] == '"')
// 			{
// 				split[j][y++] = s[i++];
// 				while (s[++i] != '"')
// 					split[j][y++] = s[i++];
// 			}
// 			if (s[i] == '&' && s[i + 1] == '&')
// 				break ;
// 			else if (s[i] == '|' && s[i + 1] == '|')
// 				break ;
// 			split[j][y++] = s[i++];
// 		}
// 		while (s[i] == '&' || s[i] == '|')
// 			i++;
// 		j++;
// 		y = 0;
// 	}
// 	return (split);
// }
