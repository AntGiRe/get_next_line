/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-rey <agil-rey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:01:31 by agil-rey          #+#    #+#             */
/*   Updated: 2022/11/03 14:01:31 by agil-rey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getleftover(char *s)
{
	int		i;
	int		counter;
	char	*leftover_part;

	counter = 0;
	i = ft_getindex(s);
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	leftover_part = (char *)malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!leftover_part)
		return (NULL);
	i++;
	while (s[i])
		leftover_part[counter++] = s[i++];
	leftover_part[counter] = '\0';
	free (s);
	return (leftover_part);
}

char	*ft_read(int fd, char *leftover_part)
{
	char	*buff;
	int		bytes;

	bytes = 1;
	buff = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!ft_strchr(leftover_part, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		leftover_part = ft_strjoin(leftover_part, buff);
	}
	free (buff);
	return (leftover_part);
}

char	*ft_putline(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	line = (char *)malloc(sizeof(char) * (ft_getindex(s)+2));
	if (!line)
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = ft_read(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_putline(buff);
	buff = ft_getleftover(buff);
	return (line);
}
