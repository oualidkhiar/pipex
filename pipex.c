/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:56:54 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/02 13:28:48 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_handle_failed(void)
{
	perror("Error failed");
	exit(1);
}

void	child_procces(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = ft_open_file(av[1], 0);
	if (dup2(fd, 0) == -1)
		ft_handle_failed();
	if (dup2(p_fd[1], 1) == -1)
		ft_handle_failed();
	close(p_fd[0]);
	exec_cmd(av[2], env);
}

void	parent_procces(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = ft_open_file(av[4], 1);
	if (dup2(fd, 1) == -1)
		ft_handle_failed();
	if (dup2(p_fd[0], 0) == -1)
		ft_handle_failed();
	close(p_fd[1]);
	exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int	pid;
	int	p_fd[2];

	if (ac != 5)
	{
		ft_putstr_fd("Argument not valid EX: <infile CMD1 CMD2 >outfile\n", 2);
		return (1);
	}
	if (pipe(p_fd) == -1)
		perror("Error");
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
