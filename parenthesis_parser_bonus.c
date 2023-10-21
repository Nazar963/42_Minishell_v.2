/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_parser_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:15:11 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/21 15:49:43 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*final_check_copy(char *str, int counter)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str) + 1 - counter, sizeof(char));
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
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

char	*final_check(char *str)
{
	int		i;
	int		counter;
	char	*new_str;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '(')
			counter++;
		else if (str[i] == ')')
			counter--;
		i++;
	}
	if (counter)
	{
		new_str = final_check_copy(str, counter);
		return (new_str);
	}
	return (str);
}

void	check_for_right_parenthesis_helper(char *s, int *double_first,
	int *open_pare, int *close_pare)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '(' && s[i + 1] == '(')
		{
			if (i == 0)
				*double_first = 1;
			*open_pare = i;
		}
		if (s[i] == ')' && s[i + 1] == ')')
		{
			*close_pare = 1;
			break ;
		}
		i++;
	}
}

char	*check_for_right_parenthesis(char *s)
{
	int		open_pare;
	int		close_pare;
	int		double_first;
	char	*new_str;

	open_pare = 0;
	close_pare = 0;
	double_first = 0;
	check_for_right_parenthesis_helper(s, &double_first,
		&open_pare, &close_pare);
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

	i = -1;
	j = 0;
	fs = 0;
	res = NULL;
	res = check_for_right_parenthesis(s);
	if (res)
		return (free(s), res);
	res = malloc(ft_strlen(s) * 2 + 1);
	while (s[++i])
	{
		if (s[i] == '\'' && fs != 2)
			fs = 1;
		if (s[i] == '\"' && fs != 1)
			fs = 2;
		res[j++] = s[i];
		if (!fs && (s[i] == '(' || s[i] == ')'))
			res[j++] = ' ';
	}
	res[j] = '\0';
	return (free(s), res);
}
