/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:45:11 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/17 11:21:37 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* char	*comillas(char const *s)
{
	int		i;
	int		n;
	char	*command;

	n = 0;
	i = 0;
	command = (char *)malloc(sizeof(char) * ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == 39)
		{
			i++;
			while (s[i] != 39)
			{
				command[n] = s[i];
				n++;
				i++;
			}
		}
		i++;
	}
	command[n] = '\0';
	return (command);
} */

static int	ft_count_s(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			count++;
		if (s[i] == 39)
			break ;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	**ft_body(char **dest, char const *src, char c)
{
	size_t			i;
	size_t			j;
	unsigned int	count;

	i = 0;
	j = 0;
	count = 0;
	while (src[i])
	{
		while (src[i] != c && src[i])
		{
			i++;
			/* if (src[i] == 39)
				dest[j++] = comillas(src); */
			if (src[i] == c || i == ft_strlen(src))
				dest[j++] = ft_substr(src, count, i - count);
		}
		while (src[i] == c && src[i])
		{
			i++;
			count = i;
		}
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_count_s(s, c) + 1));
	if (!str)
		return (NULL);
	ft_body(str, s, c);
	return (str);
}
