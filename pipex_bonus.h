/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:27:37 by oukhiar           #+#    #+#             */
/*   Updated: 2025/01/27 16:04:30 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
#include <fcntl.h>
# include <unistd.h>
#include <sys/wait.h>

void exec_cmd(char *cmd, char **env);
char *ft_check_command(char *cmd, char *path);
char *get_path(char **env);
int ft_open_file(char *file, int in_or_out);
void ft_free(char **adress);
void ft_handle_failed(void);

#endif