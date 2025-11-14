/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:35:56 by gaeducas          #+#    #+#             */
/*   Updated: 2025/11/14 12:33:39 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_extract_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n')
		i++;
	line = ft_substr(stash, 0, i + 1);
	return (line);
}

char	*ft_update_size(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n')
		i++;
	line = ft_substr(stash, i + 1, ft_strlen(stash) - (i + 1));
	if (!line)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*tmp;
	char		*line;
	int			read_bytes;

	if (BUFFER_SIZE <= 0 || (fd < 0 && fd > 1024))
		return (NULL);
	buff = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
}
