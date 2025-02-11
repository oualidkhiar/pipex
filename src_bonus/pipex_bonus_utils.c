/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:24:26 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/10 11:04:47 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (path == NULL)
		return (NULL);
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
	return (NULL);
}

char	**join_cmd_with_path(char **cmd, char **env)
{
	char	*path;
	char	**res;
	char	*new_cmd;

	res = cmd;
	path = get_path(env);
	new_cmd = ft_check_command(cmd[0], path);
	if (new_cmd != NULL)
	{
		if (access(new_cmd, F_OK | X_OK) != 0)
		{
			free(new_cmd);
			res = NULL;
		}
		else
		{
			free(cmd[0]);
			cmd[0] = new_cmd;
		}
	}
	else
		res = NULL;
	return (res);
}

char	**get_command(char *str, char **env)
{
	char	**cmd;
	char	**res;

	str = ft_strtrim(str, " ");
	cmd = ft_split(str, ' ');
	res = cmd;
	if (cmd == NULL)
		exit(1);
	if (cmd[0] == NULL)
		res = NULL;
	else if (cmd[0][0] == '.' || cmd[0][0] == '/')
	{
		if (access(cmd[0], F_OK | X_OK) != 0)
			res = NULL;
	}
	else
		res = join_cmd_with_path(cmd, env);
	free(str);
	if (!res)
		ft_free(cmd);
	return (res);
}
