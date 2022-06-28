/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:33:26 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/28 12:17:58 by ygonzale         ###   ########.fr       */
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
		printf("No such file or directory\n");
		return (0);
	}
	return (1);
}

int	ft_putchar(char c)
{
	int	dest;

	dest = 0;
	dest += write(1, &c, 1);
	return (dest);
}

int	ft_putstr(char *str)
{
	int	i;
	int	dest;

	i = 0;
	dest = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		dest += ft_putchar(str[i]);
		i++;
	}
	return (dest);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
		if (s[i + 1] == '\0')
			write (fd, "\n", 1);
	}
}

void	free_trash(char **trash)
{
	int	i;

	i = 0;
	while (trash[i])
	{
		free(trash[i]);
		i++;
	}
	free(trash);
}