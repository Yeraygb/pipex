/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:26:21 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/14 15:53:40 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 

void	child_process(int *fd, char **argv, char **envp)
{
	int		infile;
	char	**split_av;
	int		filein;
	char	*path_command;

	close(fd[1]); //cerramos el lado de escritura del pipe
	filein = open(argv[1], O_RDONLY);
	dup2(filein, STDIN_FILENO); //recibir atraves de la pipe por el standar in el fd
	close(filein);
	dup2(fd[1], STDOUT_FILENO); // meter el fd original en el standar out de la pipe//cerramos el lado de lectura del pipe
	close(fd[1]); //cerrar el lado de escrituda
	split_av = ft_split(argv[2], ' ');
	obtain_path(split_av[0], envp, &path_command);
	execve(path_command, split_av, envp);
}

void	parent_process(int *fd, char **argv, char **envp, pid_t pid)
{
	int		outfile;
	char	**split_av;
	int		fileout;
	char	*path_command;

	fileout = open(argv[4], O_WRONLY);
	close(fd[1]); //cerramos el lado de escritura del pipe
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]); //cerramos el lado de lectura del pipe
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	split_av = ft_split(argv[3], ' ');
	obtain_path(split_av[0], envp, &path_command);
	execve(path_command, split_av, envp);
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
		perror("ERROR");
		return (1);
	}
	if (s_pipex.pid == 0) //proceso hijo
		child_process(s_pipex.fd, argv, envp);
	else
	{
		waitpid(s_pipex.pid, NULL, 0);
		parent_process(s_pipex.fd, argv, envp, s_pipex.pid);
	}
	return (0);
}
