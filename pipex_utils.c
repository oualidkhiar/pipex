/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:56:21 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/01 21:11:21 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY);
	if (in_or_out == 1)
		ret = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (ret == -1)
	{
		ft_putstr_fd("failed to open the file\n", 2);
		exit(1);
	}
	return (ret);
}

char	*get_path(char **env)
{
	int		i;
	int		j;
	char	*name;

	j = 0;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		name = ft_substr(env[i], 0, j);
		if (!ft_strncmp(name, "PATH", 4))
		{
			free(name);
			return (env[i] + j + 1);
		}
		free (name);
		i++;
	}
	return (NULL);
}

char	*ft_check_command(char *cmd, char *path)
{
	char	**splited_path;
	int		i;
	char	*join_path;
	char	*join_cmd;

	i = 0;
	splited_path = ft_split(path, ':');
	while (splited_path[i])
	{
		join_path = ft_strjoin(splited_path[i], "/");
		join_cmd = ft_strjoin(join_path, cmd);
		if (!access(join_cmd, F_OK | X_OK))
		{
			free (join_path);
			ft_free (splited_path);
			return (join_cmd);
		}
		free (join_cmd);
		free (join_path);
		i++;
	}
	ft_free (splited_path);
	return (cmd);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
	{
		ft_putstr_fd("split failed, try again.\n", 2);
		exit(0);
	}
	path = get_path(env);
	if (!path)
	{
		ft_putstr_fd("Path not found, try again.\n", 2);
		ft_free(s_cmd);
		exit(0);
	}
	if (execve(ft_check_command(s_cmd[0], path), s_cmd, env) == -1)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		
		ft_free(s_cmd);
		exit(1);
	}
}

void	ft_free(char **adress)
{
	size_t	i;

	i = 0;
	while (adress[i])
	{
		free(adress[i]);
		i++;
	}
	free(adress);
}
