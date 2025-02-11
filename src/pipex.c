/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:56:54 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/10 11:12:21 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_procces(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = ft_open_file(av[1], 0);
	if (dup2(fd, 0) == -1)
		ft_handle_failed();
	if (dup2(p_fd[1], 1) == -1)
		ft_handle_failed();
	close(p_fd[0]);
	close(fd);
	close(p_fd[1]);
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
	close(fd);
	close(p_fd[0]);
	exec_cmd(av[3], env);
}

void	do_child(int *p_fd, char **av, char **env)
{
	int	i;
	int	pid;

	i = 2;
	while (i > 0)
	{
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (pid == 0)
		{
			if (i == 2)
				child_procces(av, p_fd, env);
			else
				parent_procces(av, p_fd, env);
		}
		else
			i--;
	}
}

int	main(int ac, char **av, char **env)
{
	int	p_fd[2];
	int	i;

	i = 2;
	if (ac != 5)
	{
		ft_putstr_fd("Argument not valid EX: <infile CMD1 CMD2 >outfile\n", 2);
		return (1);
	}
	if (pipe(p_fd) == -1)
		perror("Error");
	do_child(p_fd, av, env);
	close(p_fd[0]);
	close(p_fd[1]);
	while (i-- > 0)
		waitpid(0, NULL, 0);
}
