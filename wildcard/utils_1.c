/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:56:27 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/10 19:56:48 by naal-jen         ###   ########.fr       */
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
		new_new_str = ft_realloc(new_new_str, 4);
		new_new_str = ft_strjoin_free(new_new_str, " &&");
	}
	else if (**str == '|')
	{
		(*str) += 2;
		new_new_str = ft_realloc(new_new_str, 4);
		new_new_str = ft_strjoin_free(new_new_str, " ||");
	}
	return (new_new_str);
}

char	*add_command_processed(char *to_be_processed, char *new_new_str)
{
	new_new_str = ft_realloc(new_new_str, ft_strlen(to_be_processed) + 1);
	new_new_str = ft_strjoin_free(new_new_str, to_be_processed);
	return (new_new_str);
}
