/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:37:47 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/11 12:54:54 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*generate_random_name_for_the_file(int j)
{
	char	buffer[16];
	char	*ret;
	ssize_t	bytesread;
	int		fd;

	ret = malloc(5);
	fd = open("/dev/random", O_RDONLY);
	while (fd != -1)
	{
		bytesread = read(fd, buffer, 15);
		buffer[bytesread] = '\0';
		while (--bytesread >= 0)
		{
			if (j == 4)
			{
				close(fd);
				ret[j] = '\0';
				return (ret);
			}
			if (ft_isprint(buffer[bytesread]))
				ret[j++] = buffer[bytesread];
		}
	}
	free(ret);
	return (NULL);
}

char	*get_name_in_tmp(void)
{
	char	*name;
	char	*path_name;

	name = generate_random_name_for_the_file(0);
	if (name == NULL)
		return (NULL);
	path_name = ft_strjoin("/tmp/", name);
	free(name);
	return (path_name);
}

int	read_from_here_doc(char *file)
{
	char	*buffer;
	int		fd;
	char	*path_name;

	path_name = get_name_in_tmp();
	if (!path_name)
		return (-1);
	fd = open(path_name, O_RDWR | O_TRUNC | O_CREAT, 0766);
	while (fd != -1)
	{
		buffer = get_next_line(0);
		if (!buffer)
			return (-1);
		if (ft_strncmp(file, buffer, ft_strlen(file)) \
		== 0 && ft_strlen(buffer) - 1 == ft_strlen(file))
		{
			close(fd);
			fd = open(path_name, O_RDONLY, 0766);
			free(path_name);
			free (buffer);
			return (fd);
		}
		ft_putstr_fd(buffer, fd);
		free (buffer);
	}
	return (fd);
}
