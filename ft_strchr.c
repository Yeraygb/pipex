/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygonzale <ygonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:27:45 by ygonzale          #+#    #+#             */
/*   Updated: 2022/06/14 11:53:53 by ygonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Funcion busca el primer caracter que coincide en 2 strings
**
** @param {const char *s} La string en la que se quiere buscar un parametro
** @param {int c} El parametro que quieres buscar
**
** @return {char} La direc de la *s desde que ha encontrado la 1º coincidencia
*/
char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(s);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *)&s[i]);
	return (NULL);
}
