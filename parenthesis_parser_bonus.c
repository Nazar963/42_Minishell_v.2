/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_parser_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:15:11 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/24 16:44:56 by naal-jen         ###   ########.fr       */
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

char	*better_parenthesis(char *s)
{
	char	*res;
	int		i;
	int		j;
	char	fs;

	i = -1;
	j = 0;
	fs = 0;
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
