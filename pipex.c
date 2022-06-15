/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:26:21 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/15 13:38:46 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 

void	child_process(int *fd, char **argv, char **envp)
{
	char	**split_av;
	int		filein;
	char	*path_command;
/* 	int i = 0;

	while (argv[i])
	{

		printf("%s\n", argv[i]);
		i++;
	}	 */
	close(fd[1]);
	filein = open(argv[1], O_RDONLY);
	dup2(filein, STDIN_FILENO);
	//dup2(fd[1], STDOUT_FILENO);
	close(filein);
	close(fd[1]);
	split_av = ft_split(argv[2], ' ');
	obtain_path(split_av[0], envp, &path_command);
	printf("comando con el path hijo:%s\n", path_command);
	execve(path_command, split_av, envp);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	char	**split_av;
	int		fileout;
	char	*path_command;

	close(fd[1]);
	fileout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[0]);
	split_av = ft_split(argv[3], ' ');
	printf("split:%s\n", split_av[0]);
	printf("argv3:%s\n", argv[3]);
	obtain_path(split_av[0], envp, &path_command);
	printf("comando con el path padre:%s\n", path_command);
	execve(path_command, split_av, envp);
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pipex;

	if (argc != 5)
		return (printf("Number of argument invalid\n"));
	pipe (s_pipex.fd);
	s_pipex.pid = fork();
	if (s_pipex.pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (s_pipex.pid == 0)
		child_process(s_pipex.fd, argv, envp);
	else
	{
		waitpid(s_pipex.pid, NULL, 0);
		parent_process(s_pipex.fd, argv, envp);
	}
	return (0);
}
