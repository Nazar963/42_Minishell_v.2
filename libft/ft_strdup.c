/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:45:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/28 20:48:18 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_len(const char *src, int len)
{
	int		i;
	char	*res;

	i = 0;
	if (!src)
		return (NULL);
	while (*(src + i) && i <= len)
		i++;
	res = malloc(i * 8 + 8);
	i = 0;
	while (*(src + i) && i <= len)
	{
		*(res + i) = *(src + i);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}

char	*good_strdup(char *src)
{
	int		i;
	char	*res;

	i = 0;
	if (!src)
		return (NULL);
	while (*(src + i))
		i++;
	res = ft_calloc(i + 1, 8);
	i = 0;
	while (*(src + i))
	{
		while (*(src + i) == -1)
			src++;
		*(res + i) = *(src + i);
		if (!*(src + i))
			break ;
		i++;
	}
	*(res + i) = '\0';
	return (res);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*res;

	i = 0;
	if (!src)
		return (ft_calloc(1, 8));
	while (*(src + i))
		i++;
	res = ft_calloc(i + 1, 8);
	i = 0;
	while (*(src + i))
	{
		*(res + i) = *(src + i);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}

char	*ft_strdup_fr_to(const char *src, int from, int to)
{
	int		i;
	char	*res;

	i = 0;
	if (!src)
		return (NULL);
	res = (char *)ft_calloc(to - from + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (from < to)
	{
		res[i] = src[from];
		i++;
		from++;
	}
	return (res);
}

char	*ft_strdup_fr_to_free(char *src, int from, int to)
{
	int		i;
	char	*res;

	i = 0;
	if (!src)
		return (NULL);
	res = (char *)ft_calloc(to - from + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (from < to)
	{
		res[i] = src[from];
		i++;
		from++;
	}
	free(src);
	return (res);
}
