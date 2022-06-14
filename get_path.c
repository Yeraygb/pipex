/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:46:03 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/14 15:03:40 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

char	**env_path(char **envp)
{
	char	**splitpath;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			splitpath = ft_split(ft_strchr(envp[i], '/'), ':');
			return (splitpath);
		}
		i++;
	}
	return (0);
}

void	*obtain_path(char *split_av, char **envp, char	**path_command)
{
	t_path	s_path;
	int		i;

	i = 0;
	s_path.path = env_path(envp);
	while (s_path.path[i])
	{
		s_path.pathslash = ft_strjoin(s_path.path[i], "/");
		s_path.pathav = ft_strjoin(s_path.pathslash, split_av);
		s_path.fd = open (s_path.pathav, O_RDONLY);
		if (s_path.fd >= 0)
		{
			*path_command = s_path.pathav;
			close(s_path.fd);
		}
		free(s_path.pathav);
		i++;
	}
	free(s_path.path);
}
