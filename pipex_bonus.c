/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:06:59 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/02 13:00:50 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


void	ft_handle_failed(void)
{
	perror("Error failed:");
	exit(1);
}

void	child_procces(char **av, int (*p_fd1)[2], char **env, int i)
{
	int	fd;

	if (!ft_strncmp(av[1], "here_doc", 8))
		handle_here_document(av, p_fd1, env, i);
	else if (i == 0 && ft_strncmp(av[1], "here_doc", 8) != 0)
	{
		fd = ft_open_file(av[1], 0);
		if (dup2(fd, 0) == -1)
			ft_handle_failed();
		close((*p_fd1)[0]);
	}
	else
	{
		if (dup2(*(p_fd1 - 1)[0], 0) == -1)
			ft_handle_failed();
		close(*(p_fd1 - 1)[1]);
		close((*(p_fd1))[0]);
	}
	if (dup2((*(p_fd1))[1], 1) == -1)
		ft_handle_failed();
	exec_cmd(av[i + 2], env);
}

void	parent_procces(char **av, int p_fd, char **env, int index)
{
	int	fd;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		fd = ft_open_file(av[index], 3);
	else
		fd = ft_open_file(av[index], 1);
	if (dup2(p_fd, 0) == -1)
		ft_handle_failed();
	if (dup2(fd, 1) == -1)
		ft_handle_failed();
	exec_cmd(av[index - 1], env);
}

void	ft_colse(int (*p_fd)[2], int i)
{
	if (i - 1 >= 0)
		close(p_fd[i - 1][0]);
	close (p_fd[i][1]);
}

// int **ft_alocate_pipes(int count)
// {
// 	int **pipes;
// 	int i;	

// 	i = 0;
// 	pipes = malloc(sizeof(int *) * (count + 1));
// 	if (!pipes)
// 		return (NULL);
// 	while (pipes[i])
// 	{
// 		pipes[i] = malloc(sizeof(int) * 2);
// 	}
// 	pipes[i] = NULL;
// 	return (pipes);
// }

int	ft_reduce(char **av, char **env, int count)
{
	int	pid;
	int	i;
	int	p_fd[count -1][2];

	i = 0;
	// p_fd = ft_alocate_pipes(count - 1);
	while (i < count - 1)
	{
		if (pipe(p_fd[i]) == -1)
			ft_handle_failed();
		pid = fork();
		if (pid == -1)
			ft_handle_failed();
		else if (pid == 0)
		{
			if (i == 0)
				child_procces(av, p_fd, env, i);
			else
				child_procces(av, p_fd + i, env, i);
		}
		else
			ft_colse(p_fd, i);
		i++;
	}
	return (p_fd[i - 1][0]);
}

int	main(int ac, char **av, char **env)
{
	int	count;
	int	fd;

	count = ac - 3;
	if (ac < 5)
	{
		ft_putstr_fd("Argument not valid EX: <infile CMD1\
		CMD2 CMD3 >outfile\n", 2);
		exit (1);
	}
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
		{
			ft_putstr_fd("Argument not valid EX: <here_doc DILIMETE\
			CMD1 CMD2 >outfile\n", 2);
			exit (1);
		}
		else
			count = ac - 4;
	}
	fd = ft_reduce(av, env, count);
	waitpid(-1, NULL, 0);
	printf("END\n");
	parent_procces(av, fd, env, ac -1);
}
