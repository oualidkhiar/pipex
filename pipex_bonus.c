/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:06:59 by oukhiar           #+#    #+#             */
/*   Updated: 2025/01/27 21:26:39 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int read_from_here_doc(char **av)
{
    char *buffer;
    int fd;

    fd = open("file", O_RDWR | O_CREAT, 0766);
    while (1)
    {
        buffer = get_next_line(0);
        if (ft_strncmp(av[2], buffer, ft_strlen(av[2])) == 0)
        {
            free (buffer);
            return (fd);
        }
        ft_putstr_fd(buffer, fd);
        free (buffer);
    }
    return (fd);
}

void child_procces(char **av, int *p_fd1, int *p_fd2, char **env, int i)
{
    int fd;

    if (i == 0 && (ft_strncmp(av[1], "here_doc", 8) == 0))
    {
        fd = read_from_here_doc(av);
        dup2(fd, 0);
        dup2(p_fd2[1], 1);
        close(p_fd1[0]);
    }
    else if (i == 0 && ft_strncmp(av[1], "here_doc", 8) != 0)
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
    // dup2(p_fd2[1], 1);
    exec_cmd(av[i+3], env);
}

void parent_procces(char **av, int *p_fd, char **env, int index)
{
	int fd;
    printf("HNA\n");
	fd  = ft_open_file(av[index], 1);
	if (dup2(p_fd[0], 0) == -1)
        ft_handle_failed();
	if (dup2(fd, 1) == -1)
        ft_handle_failed();
	exec_cmd(av[index - 1], env);
}

int ft_reduce(char **av, char **env, int count, int (*p_fd)[2])
{
    int pid;
    int i;

    i = 0;
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
            	child_procces(av, p_fd[i], p_fd[i],env, i);
			else
				child_procces(av, p_fd[i - 1], p_fd[i], env, i);
		}
		else  
		close(p_fd[i][1]);
		i++;
    }
    return (i);
}

int main(int ac, char **av ,char **env)
{
    int count = ac - 3; 
    int p_fd[count-1][2];

    if (ac < 5)
    {
        ft_putstr_fd("Argument not valid EX: <infile CMD1 CMD2 CMD3 >outfile\n", 2);
        exit (1);
    }
    if (ft_strncmp(av[1], "here_doc", 8) == 0)
    {
        if (ac < 6)
        {
            ft_putstr_fd("Argument not valid EX: <here_doc DILIMETER CMD1 CMD2 >outfile\n", 2);
            exit (1);
        }
        else
            count = ac - 4;
    }
    int i = ft_reduce(av, env, count, p_fd);
    printf("%d\n", i);
	waitpid(-1, NULL, 0);
	printf("END\n");
    parent_procces(av, p_fd[i-1], env, ac -1);
}
