/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:06:11 by naal-jen          #+#    #+#             */
/*   Updated: 2023/11/14 20:53:02 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_match(char **split_wild, const char *str, int *i, int *j)
{
	char	*sub;
	int		sub_len;
	int		found;

	if (*split_wild && *split_wild[0] == '*' && ft_strlen(*split_wild) == 1)
		return (1);
	while (split_wild[(*j)])
	{
		sub = split_wild[(*j)];
		sub_len = ft_strlen(sub);
		found = 0;
		while (str[++(*i)])
		{
			if (ft_strncmp(&str[(*i)], sub, sub_len) == 0)
			{
				(*i) += sub_len;
				found = 1;
				break ;
			}
		}
		if (!found)
			return (0);
		(*j)++;
	}
	return (1);
}

int	match(const char *str, char **split_wild, int first_char, int last_char)
{
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	if (first_char
		&& ft_strncmp(str, split_wild[0], ft_strlen(split_wild[0])) != 0)
		return (0);
	else if (first_char)
	{
		i += ft_strlen(split_wild[0]);
		j++;
	}
	i--;
	if (!verify_match(split_wild, str, &i, &j))
		return (0);
	if (last_char
		&& ft_strncmp(&str[len - ft_strlen(split_wild[j - 1])],
			split_wild[j - 1],
			ft_strlen(&str[len - ft_strlen(split_wild[j - 1])])) != 0)
		return (0);
	return (1);
}

char	*wildcard_process(char *str, int *first, int *last, char ***split_wild)
{
	int		k;
	char	**split;
	char	*new_str;

	if (!ft_strchr(str, '*'))
		return (ft_strdup(str));
	split = ft_split(str, ' ');
	loco()->wc_after = split;
	if (ft_strlen_arr((void **)split) == 3 && ft_strchr(split[2], '*'))
		k = 2;
	else
		k = 1;
	loco()->wc_after_in = k;
	if (!shft_strchr(split[k], '*', '\'', '\"'))
		return (ft_free_tab(split), ft_strdup(str));
	if (split[k][0] != '*')
		*first = 1;
	if (split[k][ft_strlen(split[k]) - 1] != '*'
		|| (split[k][0] != '*' && ft_strlen(split[k]) != 1))
		*last = 1;
	*split_wild = ft_split(split[k], '*');
	new_str = ft_strjoin_free(ft_strdup(split[0]), " ");
	if (k == 2)
		main_command_join(&new_str, split);
	return (new_str);
}

char	*process_mutli_wild_card(char *str)
{
	char	*new_new_str;
	char	*to_be_processed;

	loco()->wild = 1;
	new_new_str = NULL;
	while (*str)
	{
		to_be_processed = split_wild(str);
		if (!shft_strchr(to_be_processed, '*', '\'', '\"'))
		{
			new_new_str = add_command_processed(to_be_processed, new_new_str);
			str += ft_strlen(to_be_processed);
			new_new_str = add_operator(new_new_str, &str);
			free(to_be_processed);
			continue ;
		}
		if (shft_strchr(to_be_processed, '(', '\'', '\"')
			|| shft_strchr(to_be_processed, ')', '\'', '\"'))
			to_be_processed = clean_cmd(to_be_processed);
		to_be_processed = check_for_wildcard_normal(to_be_processed);
		new_new_str = add_command_processed(to_be_processed, new_new_str);
		free(to_be_processed);
		new_new_str = add_operator(new_new_str, &str);
	}
	return (new_new_str);
}

char	*check_for_wildcard_normal(char *str)
{
	char	**split_wild;
	char	*new_str;
	char	*multi_new_str;
	int		first_char;
	int		last_char;

	if (loco()->wild == 0 && (loco()->and == 1 || loco()->or == 1))
	{
		multi_new_str = process_mutli_wild_card(str);
		loco()->wild = 0;
		return (multi_new_str);
	}
	initialize_three_to_zero(&first_char, &last_char, &loco()->flag_no_process);
	new_str = wildcard_process(str, &first_char, &last_char, &split_wild);
	if (ft_strncmp(str, new_str, ft_strlen(str)) == 0)
		return (free(new_str), str);
	loco()->dir = opendir(".");
	if (!loco()->dir)
		return (free(new_str), NULL);
	pr_dir(&new_str, split_wild, first_char, last_char);
	closedir(loco()->dir);
	if (!loco()->flag_no_process)
		return (free(new_str), str);
	free(str);
	return (check_for_wildcard_helper(&new_str), new_str);
}
