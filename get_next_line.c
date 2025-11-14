/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:35:56 by gaeducas          #+#    #+#             */
/*   Updated: 2025/11/14 21:58:29 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
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
	while (stash[i] && stash[i] != '\n')
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
	char		*tmp;
	char		*buff;
	char		*line;
	int			read_bytes;

	read_bytes = 1;
	if ((BUFFER_SIZE <= 0 || fd < 0) && fd > 1024)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (read_bytes > 0 && ft_strchr(stash, '\n') == NULL)
	{
		read_bytes = (int)read(fd, stash, BUFFER_SIZE + 1);
		if (read_bytes < 0)
		{
			if (!stash)
			{
				free(stash);
				stash = NULL;
			}
			return (NULL);
		}
		buff[read_bytes] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buff);
		free(tmp);
	}
	line = ft_extract_line(stash);
	if (!line)
		return (NULL);
	stash = ft_update_size(stash);
	free(stash);
	return (line);
}

/*
appeler fonction chercher la ligne
secu
extraire (modifier stash)
return line


edit join (ou pas)
*/