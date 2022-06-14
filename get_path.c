/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:46:03 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/14 13:00:50 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

char	**env_path(char **envp)
{
	t_path	s_path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			s_path.path = ft_split(ft_strchr(envp[i], '/'), ':');
			return (s_path.path);
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
	s_path.pathget = env_path(envp);
	while (s_path.pathget[i])
	{
		s_path.pathjoin = ft_strjoin(s_path.pathget[i], "/");
		s_path.pathav = ft_strjoin(s_path.pathjoin, split_av);
		s_path.fd = open (s_path.pathav, O_RDONLY);
		if (s_path.fd >= 0)
		{
			*path_command = s_path.pathav;
			return ;
		}
		free(s_path.pathav);
		i++;
	}
	free(s_path.path);
}
