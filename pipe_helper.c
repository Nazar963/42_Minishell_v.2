/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:46:25 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/12 22:04:43 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shft_clean_tempfiles(t_shell_stuff *sh)
{
	char	**temp1;
	int		i;

	temp1 = ft_split("/usr/bin/rm|-f|.tempfile", '|');
	if (!access(".tempfile", F_OK) && !fork())
		execve(temp1[0], temp1, shft_dupenv(sh));
	free(temp1[2]);
	temp1[2] = ft_strdup(".tempfile1");
	if (!access(".tempfile1", F_OK) && !fork())
		execve(temp1[0], temp1, shft_dupenv(sh));
	i = 0;
	free(temp1[2]);
	temp1[2] = ft_strdup(".heredoc0");
	while (i < 10)
	{
		temp1[2][8] = '0' + i++;
		if (!access(temp1[2], F_OK) && !fork())
			execve(temp1[0], temp1, shft_dupenv(sh));
	}
	ft_free_tab(temp1);
	return ;
}

char	*shft_strstr(char *haystack, const char *needle)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	fs;

	i = 0;
	fs = 0;
	n_len = ft_strlen(needle);
	if (!n_len || haystack == needle)
		return (haystack);
	while (haystack[i])
	{
		c = 0;
		fs ^= fs_check(fs, haystack[i]);
		while (haystack[i + c] != '\0' && needle[c] != '\0'
			&& haystack[i + c] == needle[c] && !fs)
			c++;
		if (c == n_len)
			return (haystack + i);
		i++;
	}
	return (NULL);
}

char	*cmd_appender(char *str, char *what)
{
	char	*res;
	char	*refs[3];

	res = ft_calloc(ft_strlen(str) + ft_strlen(what) + 5, sizeof(char));
	refs[0] = res;
	refs[1] = str;
	refs[2] = what;
	while (*str && *str != -1)
		*(res++) = *(str++);
	while (*str == -1)
		str++;
	while (*what)
		*(res++) = *(what++);
	while (*str)
		*(res++) = *(str++);
	*res = '\0';
	return (refs[0]);
}

char	shft_manage_limiter(char **str, t_shell_stuff *sh)
{
	char		*cmd;
	char		*limiter;
	char		*hd_name;
	static int	i = 0;

	cmd = shft_strstr(*str, "<<");
	if (!cmd)
		return (i = 0, 0);
	hd_name = ft_strdup(".heredoc0");
	hd_name[8] = '0' + i++;
	limiter = shft_get_word(cmd + 2);
	if (!limiter || !*limiter)
	{
		ft_putstr_fd(SYNTERR, STDERR_FILENO);
		return (i = 0, 1);
	}
	clean_stuff(cmd, ft_strlen(limiter));
	*str = cmd_appender(*str, ft_strjoin("<", hd_name));
	if (read_stdin(limiter, sh, hd_name))
		return (i = 0, 1);
	free(limiter);
	free(hd_name);
	return (shft_manage_limiter(str, sh));
}
