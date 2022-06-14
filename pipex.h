/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:23:52 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/14 13:21:26 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex
{
	pid_t	pid;
	int		fd[2];
}	t_pipex;

typedef struct s_path
{
	char	**path;
	char	**pathget;
	char	*pathslash;
	char	*pathav;
	int		fd;
}	t_path;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
void	*obtain_path(char *split_av, char **envp, char	**path_command);
char	**env_path(char **envp);
size_t	ft_strlen(const char *str);

#endif