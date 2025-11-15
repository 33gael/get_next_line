/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:35:56 by gaeducas          #+#    #+#             */
/*   Updated: 2025/11/15 15:07:47 by gaeducas         ###   ########.fr       */
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

// char	*get_next_line(int fd)
// {
// 	static char	*stash;
// 	char		*tmp;
// 	char		*buff;
// 	char		*line;
// 	int			read_bytes;

// 	read_bytes = 1;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buff)
// 		return (NULL);
// 	while (!stash || (read_bytes > 0 && ft_strchr(stash, '\n') == NULL))
// 	{
// 		read_bytes = read(fd, buff, BUFFER_SIZE);
// 		if (read_bytes < 0)
// 		{
// 			free(buff);
// 			if (stash)
				// Correction de la fuite : libère le contenu partiellement lu
// 				free(stash);
// 			stash = NULL;
// 			return (NULL);
// 		}
// 		if (read_bytes == 0) // Ajouter un break pour la fin de fichier
// 			break ;
// 		buff[read_bytes] = '\0';
// 		tmp = stash;
// 		stash = ft_strjoin(tmp, buff);
// 		free(tmp);
// 		if (!stash) // Sécurité si ft_strjoin échoue
// 		{
// 			free(buff);
// 			return (NULL);
// 		}
// 	}
// 	free(buff);
// 	if (!stash || stash[0] == '\0')
// 	{
// 		free(stash);
// 		stash = NULL;
// 		return (NULL);
// 	}
// 	line = ft_extract_line(stash);
// 	if (!line)
// 	{
// 		free(stash); // Libérer stash si l'extraction échoue
// 		stash = NULL;
// 		return (NULL);
// 	}
// 	tmp = ft_update_size(stash);
// 	stash = tmp;
// 	return (line);
// }

static char	*ft_read_loop(int fd, char *stash)
{
	char	*buff;
	char	*tmp;
	int		read_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (free(stash), NULL);
	read_bytes = 1;
	while (!stash || (read_bytes > 0 && ft_strchr(stash, '\n') == NULL))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buff), free(stash), NULL);
		if (read_bytes == 0)
			break ;
		buff[read_bytes] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buff);
		free(tmp);
		if (!stash)
			return (free(buff), NULL);
	}
	free(buff);
	return (stash);
}

static char	*ft_finalize(char **stash)
{
	char	*line;
	char	*tmp;

	if (!*stash || **stash == '\0')
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	line = ft_extract_line(*stash);
	if (!line)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	tmp = ft_update_size(*stash);
	*stash = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_loop(fd, stash);
	if (!stash)
		return (NULL);
	return (ft_finalize(&stash));
}
