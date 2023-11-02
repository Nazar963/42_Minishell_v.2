/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:56:27 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/02 17:46:15 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_operator(char *new_new_str, char **str)
{
	while (**str && (**str != '&' && **str != '|'))
		(*str)++;
	if (**str == '&')
	{
		(*str) += 2;
		new_new_str = ft_strjoin_free(new_new_str, " &&");
	}
	else if (**str == '|')
	{
		(*str) += 2;
		new_new_str = ft_strjoin_free(new_new_str, " ||");
	}
	return (new_new_str);
}

char	*add_command_processed(char *to_be_processed, char *new_new_str)
{
	new_new_str = ft_strjoin_free(new_new_str, to_be_processed);
	return (new_new_str);
}

int	split_wild_size(char *str)
{
	int	z;

	z = -1;
	while (str[++z])
	{
		if (str[z] == '\'')
		{
			z++;
			while (str[z] != '\'')
				z++;
		}
		if (str[z] == '"')
		{
			z++;
			while (str[z] != '"')
				z++;
		}
		if ((str[z] == '&' && str[z + 1] == '&')
			|| (str[z] == '|' && str[z + 1] == '|'))
			break ;
	}
	return (z);
}

char	*split_wild_fill_new_str(char *str, char *new_str)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			new_str[++j] = str[i++];
			while (str[i] != '\'')
				new_str[++j] = str[i++];
		}
		if (str[i] == '"')
		{
			new_str[++j] = str[i++];
			while (str[i] != '\'')
				new_str[++j] = str[i++];
		}
		if ((str[i] == '&' && str[i + 1] == '&')
			|| (str[i] == '|' && str[i + 1] == '|'))
			return (new_str);
		new_str[++j] = str[i++];
	}
	return (new_str);
}
