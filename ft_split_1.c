/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:45:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/10 22:50:50 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ppsplit_isok(char *str)
{
	int	test;

	test = 1;
	while (*str && *str != '|')
	{
		if (*str == '\'' || *str == '\"')
			test = !test;
		str++;
	}
	if (*str == '|' && test)
	{
		str++;
		if (*str == '|')
			return (2);
		while (shft_istab(*str))
			str++;
		if (*str == '|')
			return (1);
		return (ppsplit_isok(str));
	}
	return (0);
}

int	shft_split1_test(char *s, char ig1, char ig2, int test)
{
	if (test < 0)
		test = -test;
	if (s[0] == ig1 && test != 2)
		test ^= 1;
	if (s[0] == ig2 && test != 1)
		test ^= 2;
	return (test);
}

static char	**shft_split1_1(char *s, char c, int *i, int *j)
{
	if (ppsplit_isok(s) != 2 && ppsplit_isok(s))
	{
		ft_putstr_fd("Pipe: empty pipeline node\n", STDERR_FILENO);
		return (NULL);
	}
	shft_init_two_vars(i, 0, j, 0);
	while (shft_istab(s[*i]))
		*i = *i + 1;
	return (ft_calloc((count_words(s, c) + 1), 8));
}

char	**shft_split1(char *s, char c, char ig1, char ig2)
{
	t_vector2_int	v;
	int				test_ind[2];
	char			**split;

	split = shft_split1_1(s, c, &v.a, &v.b);
	shft_init_two_vars(&test_ind[0], 0, &test_ind[1], -1);
	if (!split)
		return (NULL);
	while (v.a <= ft_strlen(s))
	{
		test_ind[0] = shft_split1_test((char *)s + v.a, ig1, ig2, test_ind[0]);
		if (s[v.a] != c && test_ind[1] < 0)
			test_ind[1] = v.a;
		else if (((s[v.a] == c && s[v.a + 1] != c && s[v.a - 1] != c \
				&& !test_ind[0]) || v.a == ft_strlen(s)) && test_ind[1] >= 0)
		{
			split[v.b++] = word_dup(s, test_ind[1], v.a);
			test_ind[1] = -1;
			while (s[v.a] && shft_istab(s[v.a + 1]))
				v.a++;
		}
		v.a++;
	}
	split[v.b] = NULL;
	return (split);
}

char	**shft_split(char const *s, char c, char ig1, char ig2)
{
	int		i;
	int		j;
	int		index;
	char	**split;
	int		test;

	split = ft_calloc(count_words_1(s, c) + ft_strlen(s), 8);
	if (!s || !split)
		return (0);
	shft_init_two_vars(&i, 0, &j, 0);
	shft_init_two_vars(&test, 0, &index, -1);
	while (i <= ft_strlen(s))
	{
		test = shft_split1_test((char *)s + i, ig1, ig2, -test);
		if (s[i] != c && index < 0)
			index = i;
		else if (((s[i] == c && test != 2) || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
