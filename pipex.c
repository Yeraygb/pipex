/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:26:21 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/14 13:20:25 by ygonzale         ###   ########.fr       */
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
	char	*dir[] = {"ls", "-l", 0};
	int		file;
	char	*path_command;

	close(fd[1]); //cerramos el lado de escritura del pipe
	file = open("infile", O_RDONLY);
	dup2(fd[1], STDOUT_FILENO); // meter el fd original en el standar out de la pipe
	close(fd[0]); //cerramos el lado de lectura del pipe
	dup2(file, STDIN_FILENO); //recibir atraves de la pipe por el standar in el fd
	close(fd[1]); //cerrar el lado de escrituda
	close(file);
	split_av = ft_split(argv[2], ' ');
	obtain_path(split_av[0], envp, &path_command);
	execve(path_command, split_av, envp);
}

void	parent_process(int *fd, char **argv, char **envp, pid_t pid)
{
	int		outfile;
	char	**split_av;
	char	*dir2[] = {"wc", "-l", 0};
	int		file;
	char	*path_command;

	waitpid(pid, NULL, 0); //espera al proceso hijo
	file = open("outfile", O_WRONLY);
	close(fd[1]); //cerramos el lado de escritura del pipe
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]); //cerramos el lado de lectura del pipe
	dup2(file, STDOUT_FILENO);
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
		parent_process(s_pipex.fd, argv, envp, s_pipex.pid);
	return (0);
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