/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:33:14 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/24 12:59:46 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 

void create_mid_process(int fd, int *fd2, char *argv, char **envp)
{
	char	**split_av;
	char	*path_command;

	//fd2[0] = open()
	dup2(fd, STDOUT_FILENO);
	dup2(fd2[1], STDIN_FILENO);
	close(fd);
	close(fd2[1]);
	split_av = ft_split(argv, ' ');
	obtain_path(split_av[0], envp, &path_command);
	execve(path_command, split_av, envp);
}

void	child_process(int *fd, char **argv, char **envp)
{
	char	**split_av;
	int		filein;
	char	*path_command;

	close(fd[0]);
	filein = open(argv[1], O_RDONLY);
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[1]);
	close(filein);
	split_av = ft_split(argv[2], ' ');
	obtain_path(split_av[0], envp, &path_command);
	execve(path_command, split_av, envp);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	char	**split_av;
	int		fileout;
	char	*path_command;

	split_av = 0;
	close(fd[1]);
	fileout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(fileout, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	split_av = ft_split(argv[3], ' ');
	obtain_path(split_av[0], envp, &path_command);
	execve(path_command, split_av, envp);
	exit (0);
}

void	mid_child_process(int *fd, char	**argv, char **envp)
{
	int		fd2[2];
	pid_t	pid2;
	int		i;

	i = 3;
	pipe(fd2);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		return ;
	}
	else if(pid2 == 0)
	{
		while (argv[i])
		{
			create_mid_process(fd[0], fd2, argv[i], envp);
			i++;
		}
	}
	else
	{
		waitpid(pid2, NULL, 0);
		parent_process(fd2, argv, envp);
	}
	
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pipex;

/* 	if (argc != 5)
		return (printf("Number of argument invalid\n")); */
	pipe (s_pipex.fd);
	s_pipex.pid = fork();
	if (s_pipex.pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (s_pipex.pid == 0)
	{
		child_process(s_pipex.fd, argv, envp);
		mid_child_process(s_pipex.fd, argv, envp);
	}
	else
	{
		waitpid(s_pipex.pid, NULL, 0);
		parent_process(s_pipex.fd, argv, envp);
	}
	return (0);
}
