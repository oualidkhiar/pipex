/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:27:37 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/10 11:27:47 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_usage
{
	int	child_pid;
	int	i;
	int	**p_fd;
	int	fd_in;
	int	fd_out;
	int	count;
}	t_usage;

int		get_in_file_from_here_doc(char *file);
int		get_in_file_from_file(char *file);
int		get_out_file_fd(char *file, char *str);
int		check_here_doc(char *str);
int		exec_cmd(char *cmd, char **env);
char	*ft_check_command(char *cmd, char *path);
char	*get_path(char **env);
void	ft_free(char **adress);
void	ft_handle_failed(void);
char	**get_command(char *str, char **env);
int		read_from_here_doc(char *file);
char	*generate_random_name_for_the_file(int j);
int		**ft_alocate_pipes(int count);
void	ft_free_pipes(int **adress_pipes);
void	*ft_malloc(size_t size);
void	ft_close_pipes(t_usage values);
int		first_child(int *p_fd1, int fd, char **env, char *av);
int		last_child_procces(int *p_fd1, int out_fd, char **env, char *av);
int		two_child(int *p_fd1, int *p_fd2, char **env, char *av);
char	*get_name_in_tmp(void);

#endif