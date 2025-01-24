/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:39:00 by oukhiar           #+#    #+#             */
/*   Updated: 2025/01/24 13:15:35 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
#include <fcntl.h>
# include <unistd.h>
#include <sys/wait.h>

int ft_open_file(char *file, int in_or_out)
{
	int ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY);
	if (in_or_out == 1)
		ret = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (ret == -1)
		exit(1);
	return(ret);
}

char *get_path(char **env)
{
	int i;
	int j;
	char *name;
	int cmp;

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

char *ft_check_command(char *cmd, char *path)
{
	char **splited_path;
	int i;
	char *join_path;
	char *join_cmd;

	i = 0;
	splited_path = ft_split(path, ':');	
	while (splited_path[i])
	{
		join_path = ft_strjoin(splited_path[i], "/");
		join_cmd = ft_strjoin(join_path, cmd);
		if (!access(join_cmd, F_OK | X_OK))
		{
			free (join_path);
			free (splited_path);
			return (join_cmd);
		}
		free (join_cmd);
		free (join_path);
		i++;
	}
	free (splited_path);
	return (cmd);
}

void exec_cmd(char *cmd, char **env)
{
	char **s_cmd;
	char *path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(env);
	if (execve(ft_check_command(s_cmd[0], path), s_cmd, env) == -1)
	{
		perror("Error");
		free(s_cmd);
		exit(1);
	}
}

void child_procces(char **av, int *p_fd1, int *p_fd2, char **env, int i)
{
    int fd;

    if (i == 0)
    {
        fd = ft_open_file(av[1], 0);
        dup2(fd, 0);
        close(p_fd1[0]);
    }
    else
    {
        dup2(p_fd1[0], 0);
		close(p_fd1[1]);
		close(p_fd2[0]);
    }
    dup2(p_fd2[1], 1);
    exec_cmd(av[i+2], env);
}
void parent_procces(char **av, int *p_fd, char **env, int index)
{
	int fd;
	fd  = ft_open_file(av[index], 1);
	dup2(p_fd[0], 0);
	dup2(fd, 1);
	exec_cmd(av[index - 1], env);
}


int main(int ac, char **av ,char **env)
{
    int count = ac - 3; 
    int p_fd[count-1][2];
    int pid;
    int i;

    i = 0;
    while (i < count - 1)
    {
		pipe(p_fd[i]);
        pid = fork();
        if (pid == 0)
		{
			if (i == 0)
            	child_procces(av, p_fd[i], p_fd[i],env, i);
			else
				child_procces(av, p_fd[i - 1], p_fd[i], env, i);
		}
		else
    	{
			close(p_fd[i][1]);
    	}
		i++;
    }
	waitpid(-1, NULL, 0);
	printf("END\n");
    parent_procces(av, p_fd[i-1], env, ac -1);
}
