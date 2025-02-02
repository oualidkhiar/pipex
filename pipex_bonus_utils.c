/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:24:26 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/01 22:28:53 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY);
	if (in_or_out == 1)
		ret = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (in_or_out == 3)
		ret = open(file, O_CREAT | O_WRONLY | O_APPEND, 0744);
	if (in_or_out == 2)
		ret = open("/dev/random", O_RDONLY);
	if (ret == -1)
		ft_handle_failed();
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
			ft_free(splited_path);
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
		exit(1);
	}
	path = get_path(env);
	if (!path)
	{
		ft_putstr_fd("Path not found, try again.\n", 2);
		ft_free(s_cmd);
		exit(1);
	}
	if (execve(ft_check_command(s_cmd[0], path), s_cmd, env) == -1)
	{
		perror("Error");
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
