/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:44:21 by aroux             #+#    #+#             */
/*   Updated: 2025/05/12 14:55:05 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	*gc_calloc(t_data *data, size_t nmemb, size_t size);

char	*gc_strdup(t_data *data, const char *s)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	str = gc_calloc(data, len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0' && i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

static void	*gc_calloc(t_data *data, size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = gc_malloc(data, nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
