/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:56:54 by oukhiar           #+#    #+#             */
/*   Updated: 2025/01/24 13:20:12 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_procces(char **av, int *p_fd, char **env)
{
	int fd;

	fd  = ft_open_file(av[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1],1);
	close(p_fd[0]);
	exec_cmd(av[2], env);
}

void parent_procces(char **av, int *p_fd, char **env)
{
	int fd;

	fd  = ft_open_file(av[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec_cmd(av[3], env);
}

int main(int ac, char **av, char **env)
{
	int pid;
	int p_fd[2];

	if (ac != 5)
		return (1);
	pipe(p_fd);
	pid = fork();
	if (pid == -1)
			perror("Error");
	if (pid == 0)
		child_procces(av, p_fd, env);
	else
	{
		wait (NULL);
		parent_procces(av, p_fd, env);
	}
}
