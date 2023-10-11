/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:56:27 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/11 10:21:13 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
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

int	shft_isallnum(char *s)
{
	while (*s <= '9' && *s >= '0')
		s++;
	if (*s != '=' && (shft_istab(*s) || !*s))
		return (1);
	return (0);
}
