/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 10:38:07 by naal-jen          #+#    #+#             */
/*   Updated: 2023/10/10 19:32:16 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../minishell.h"

char	*ft_realloc(char *pointer, int size)
{
	int		i;
	char	*new_pointer;

	i = 0;
	new_pointer = (char *)ft_calloc(sizeof(char), size);
	if (!new_pointer)
		return (NULL);
	if (!pointer)
		return (new_pointer);
	while (pointer[i])
	{
		new_pointer[i] = pointer[i];
		i++;
	}
	if (pointer)
		free(pointer);
	return (new_pointer);
}

char	*split_wild(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		z;

	i = 0;
	j = -1;
	z = -1;
	while (str[++z])
	{
		if ((str[z] == '&' && str[z + 1] == '&')
			|| (str[z] == '|' && str[z + 1] == '|'))
			break ;
	}
	new_str = (char *)ft_calloc((z + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '&' && str[i + 1] == '&')
			|| (str[i] == '|' && str[i + 1] == '|'))
			return (new_str);
		new_str[++j] = str[i++];
	}
	return (new_str);
}

void	main_command_join(char **new_str, char **split)
{
	*new_str = ft_strjoin_free(*new_str, split[1]);
	*new_str = ft_strjoin_free(*new_str, " ");
}

void	initialize_three_to_zero(int *n, int *i, int *z)
{
	*n = 0;
	*i = 0;
	*z = 0;
}

void	pr_dir(char **new_str, char **split_wild, int first, int last_char)
{
	loco()->entry = readdir(loco()->dir);
	while (loco()->entry != NULL)
	{
		if (strcmp(loco()->entry->d_name, ".") == 0
			|| strcmp(loco()->entry->d_name, "..") == 0)
		{
			loco()->entry = readdir(loco()->dir);
			continue ;
		}
		if (match(loco()->entry->d_name, split_wild, first, last_char) != 0)
		{
			*new_str = ft_strjoin_free(*new_str, loco()->entry->d_name);
			*new_str = ft_strjoin_free(*new_str, " ");
			loco()->flag_no_process = 1;
		}
		loco()->entry = readdir(loco()->dir);
	}
}

//! Old version
// char	*split_wild(char **str)
// {
// 	char	*new_str;
// 	char	*remaining_str;
// 	int		i;

// 	i = 0;
// 	while (**str && (**str == '&' || **str == '|'))
// 		str++;
// 	while ((*str)[i])
// 	{
// 		if (((*str)[i] == '&' && (*str)[i + 1] == '&')
// 			|| ((*str)[i] == '|' && (*str)[i + 1] == '|'))
// 			break ;
// 		i++;
// 	}

// 	new_str = (char *)ft_calloc((i + 1), sizeof(char));
// 	if (!new_str)
// 		return (NULL);
// 	while (**str)
// 	{
// 		if ((**str == '&' && *((*str) + 1) == '&')
// 			|| (**str == '|' && *((*str) + 1) == '|'))
// 		{
// 			remaining_str = ft_strdup(*str);
// 			if (!remaining_str)
// 			{
// 				free(new_str);  // Free allocated memory if allocation fails
// 				return (NULL);
// 			}

// 			// Free the original string
// 			free(*str);

// 			// Update the source string pointer to 
//			//point to the new string for the remaining portion
// 			*str = remaining_str;
// 			return (new_str);
// 		}
// 		*new_str = **str;
// 		new_str++;
// 		(*str)++;
// 		remaining_str = ft_strdup(*str);
// 		if (!remaining_str)
// 		{
// 			free(new_str);  // Free allocated memory if allocation fails
// 			return (NULL);
// 		}

// 		// Free the original string
// 		free((str));

// 		// Update the source string pointer to point to the new
//		//string for the remaining portion
// 		*str = remaining_str;
// 	}
// 	return (new_str);
// }