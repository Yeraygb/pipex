/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:26:21 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/10 15:40:07 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 

void	chill_process(int *fd, char **argv, char **envp)
{
	int		infile;
	//char	**split_av;
	char 	*dir[] = {"ls", "-l", 0};
	int		file;

	//close(fd[1]); //cerramos el lado de escritura del pipe
	file = open("infile", O_RDONLY);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]); //cerramos el lado de lectura del pipe
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(file);
	//split_av = ft_split(argv[2], ' ');
	execve("../bin/ls", dir, envp);
}

void	parent_process(int *fd, char **argv, char **envp, pid_t pid)
{
	int		outfile;
	//char	**split_av;
	char	*dir2[] = {"wc", "-l", 0};
	int		file;

	waitpid(pid, NULL, 0); //espera al proceso hijo
	file = open("outfile", O_WRONLY);
	close(fd[1]); //cerramos el lado de escritura del pipe
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]); //cerramos el lado de lectura del pipe
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	//split_av = ft_split(argv[2], ' ');
	execve("../usr/bin/wc", dir2, envp);
}


/* char *obtain_path(char **envp)
{
	t_path	s_path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 4))
		{
			s_path.path = ft_split(envp[i], ':');
			s_path.pathjoin = ft_strjoin(s_path.path, "/");
		}
		i++;
	}
	return(s_path.pathjoin);
} */


int	main(int argc, char **argv, char **envp)
{
	t_pipex s_pipex;
	char	**path;

	//path = obtain_path(envp);
/* 	if (argc != 5)
		return (ft_print("Number of argument invalid\n")); */
	pipe (s_pipex.fd);
	s_pipex.pid = fork();
	if (s_pipex.pid == -1)
	{
		perror("fork");
		return 1;
	}
	if (s_pipex.pid == 0) //proceso hijo
		chill_process(s_pipex.fd, argv, envp);
	else
		parent_process(s_pipex.fd, argv, envp, s_pipex.pid);
	return 0;
} 

/* int main (void)
{
	int id = fork();
	if (id == 0)
		fork();
	printf("hello word from id: %d\n", id);
	if (id == 0)
		printf("chil procces\n");
	else
		printf("main procces\n");
	return (0);
} */




/* #include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h> 

int      glob = 6;		
char     buf[] = "a write to stdout\n";

int main(void) {
			int     var;	
			pid_t   pid;

			var = 88;
			if (write( STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1) {
				printf("write error\n");
				exit(-1);
			}
			
			printf("before fork\n");
				

			if ( (pid = fork()) < 0) {
				printf("fork error\n");
				exit(-1);
			}
			
			else if (pid == 0) {		
				glob++;		               
				var++;
			} else
			sleep(2);      			

			printf("pid = %d, ppid=%d, glob = %d, var = %d\n", getpid(), getppid(), glob, var);
			exit(0);
}
 */