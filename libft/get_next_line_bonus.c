/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:37:04 by oukhiar           #+#    #+#             */
/*   Updated: 2025/01/27 10:48:53 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_newline(char *res)
{
	int	i;

	i = 0;
	if (!res)
		return (-1);
	while (res[i] != '\0')
	{
		if (res[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_reducing(int fd, char **res, int *newline_index, char *buff)
{
	ssize_t	bytes_read;
	char	*tmp;

	while (*newline_index == -1)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
		{
			free (*res);
			*res = NULL;
			break ;
		}
		*(buff + bytes_read) = 0;
		tmp = *res;
		*res = ft_strjoin(*res, buff);
		if (!*res)
		{
			free(tmp);
			break ;
		}
		free(tmp);
		*newline_index = check_newline(*res);
	}
}

void	read_until_newline(int fd, char **res, int *newline_index)
{
	char	*buff;

	*newline_index = check_newline(*res);
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return ;
	ft_reducing(fd, res, newline_index, buff);
	free (buff);
}

char	*extract_update(int fd)
{
	static char	*res[OPEN_MAX];
	char		*tmp;
	int			newline_index;
	char		*ret;

	read_until_newline(fd, &res[fd], &newline_index);
	if (!res[fd])
		return (NULL);
	if (newline_index == -1)
	{
		ret = res[fd];
		res[fd] = NULL;
		return (ret);
	}
	ret = ft_substr(res[fd], 0, newline_index + 1);
	if (!ret)
		return (NULL);
	tmp = res[fd];
	res[fd] = ft_substr(res[fd], newline_index + 1, INT_MAX);
	if (!res[fd])
		return (NULL);
	free(tmp);
	return (ret);
}

char	*get_next_line(int fd)
{
	char	*res;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	res = extract_update(fd);
	return (res);
}
