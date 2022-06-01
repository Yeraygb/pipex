/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:26:21 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/01 17:08:27 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

void	chill_process(int *fd, char argv)
{
	int outfile;

	close(fd[1]); //cerramos el lado de escritura del pipe
	outfile = open(argv, O_WRONLY | O_APPEND);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]); //cerramos el lado de lectura del pipe
	dup2(outfile, STDOUT_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex s_pipex;
	
	if (argc != 5)
		return (ft_print("Number of argument invalid\n"));
	pipe (s_pipex.fd);
	s_pipex.pid = fork();
	if (s_pipex.pid == -1)
	{
		perror("fork");
		return 1;
	}
	if (s_pipex.pid == 0) //proceso hijo
		chill_process(s_pipex.fd, argv[1]);
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