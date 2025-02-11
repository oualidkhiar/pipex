/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:23:44 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/10 11:02:09 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	first_child(int *p_fd1, int fd, char **env, char *av)
{
	char	**cmd;

	cmd = get_command(av, env);
	if (cmd)
	{
		if (dup2(fd, 0) == -1)
			return (0);
		if (dup2(p_fd1[1], 1) == -1)
			return (0);
		close(fd);
		close(p_fd1[0]);
		close(p_fd1[1]);
		execve(cmd[0], cmd, env);
	}
	else
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}

int	two_child(int *p_fd1, int *p_fd2, char **env, char *av)
{
	char	**cmd;

	cmd = get_command(av, env);
	if (cmd)
	{
		if (dup2(p_fd1[0], 0) == -1)
			return (0);
		if (dup2(p_fd2[1], 1) == -1)
			return (0);
		close(p_fd1[0]);
		close(p_fd1[1]);
		close(p_fd2[0]);
		close(p_fd2[1]);
		execve(cmd[0], cmd, env);
	}
	else
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}

int	last_child_procces(int *p_fd1, int out_fd, char **env, char *av)
{
	char	**cmd;

	cmd = get_command(av, env);
	if (cmd)
	{
		if (dup2(p_fd1[0], 0) == -1)
			return (0);
		if (dup2(out_fd, 1) == -1)
			return (0);
		close(out_fd);
		close(p_fd1[0]);
		close(p_fd1[1]);
		execve(cmd[0], cmd, env);
	}
	else
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}
