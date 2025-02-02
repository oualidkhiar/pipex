/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:37:47 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/01 22:29:52 by oukhiar          ###   ########.fr       */
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
	fd = ft_open_file("/dev/random", 2);
	while (1)
	{
		bytesread = read(fd, buffer, 15);
		if (bytesread == -1)
			ft_handle_failed();
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
}

int	read_from_here_doc(char **av)
{
	char	*buffer;
	int		fd;
	char	*name;
	char	*path_name;
	int		j;

	j = 0;
	name = generate_random_name_for_the_file(j);
	path_name = ft_strjoin("/tmp/", name);
	free(name);
	fd = open(path_name, O_RDWR | O_TRUNC | O_CREAT, 0766);
	while (1)
	{
		buffer = get_next_line(0);
		if (ft_strncmp(av[2], buffer, ft_strlen(av[2])) == 0)
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
}

void	handle_here_document(char **av, int (*p_fd1)[2], char **env, int i)
{
	int	fd;

	if (i == 0)
	{
		fd = read_from_here_doc(av);
		dup2(fd, 0);
		close((*p_fd1)[0]);
	}
	else
	{
		dup2((*(p_fd1 - 1))[0], 0);
		close(*(p_fd1 - 1)[1]);
		close((*(p_fd1))[0]);
	}
	dup2((*(p_fd1))[1], 1);
	exec_cmd(av[i + 3], env);
}