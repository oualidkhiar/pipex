/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:21:32 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/10 11:03:26 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_here_doc(char *str)
{
	if (!ft_strncmp(str, "here_doc", ft_strlen(str)) \
	&& !ft_strncmp("here_doc", str, 8))
		return (1);
	return (0);
}

int	get_in_file_from_file(char *file)
{
	return (open(file, O_RDONLY));
}

int	get_out_file_fd(char *file, char *str)
{
	if (check_here_doc(str))
		return (open(file, O_CREAT | O_WRONLY | O_APPEND, 0744));
	return (open(file, O_CREAT | O_WRONLY | O_TRUNC, 0744));
}

int	get_in_file_from_here_doc(char *file)
{
	return (read_from_here_doc(file));
}
