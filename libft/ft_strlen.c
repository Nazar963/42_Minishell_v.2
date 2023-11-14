/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:45:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/14 12:45:25 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_strlen(const char *str)
{
	size_t	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlen_arr(void	**loco)
{
	size_t	i;

	i = 0;
	while (loco[i])
		i++;
	return (i);
}
