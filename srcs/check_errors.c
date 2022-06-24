/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:56:33 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/24 16:40:37 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <fcntl.h>

int	infile_error(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("%s: ", argv[1]);
		printf("No such file or directory");
		return (0);
	}
	return (1);
}

/* int outfile_error(int argc, char **argv)
{
	int fd;

	fd = open(argv[argc - 1], O_RDONLY);
	if (fd == -1)
	{
		printf("%s: ", argv[argc - 1]);
		printf("No such file or directory");
		return (0);
	}
	return (1);
} */