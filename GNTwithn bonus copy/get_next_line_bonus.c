/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaafridi <yaafridi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:38:40 by yaafridi          #+#    #+#             */
/*   Updated: 2024/01/17 21:58:08 by yaafridi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *str)
{
	char	*buff;
	int		len;

	buff = malloc((size_t)(BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	len = 1;
	while (!ft_strchr(str, '\n') && (len != 0))
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[len] = '\0';
		str = ft_strjoin_mod(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_line(char *str)
{
	int		i;
	char	*line_new;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line_new = (char *)malloc(sizeof(char) * (i + 2));
	if (!line_new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line_new[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line_new[i] = str[i];
		i++;
	}
	line_new[i] = '\0';
	return (line_new);
}

char	*ft_skip(char *old_buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (old_buffer[i] != '\0' && old_buffer[i] != '\n')
		i++;
	if (old_buffer[i] == '\0')
	{
		free(old_buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen(old_buffer) - i + 1));
	if (new_buffer == NULL)
		return (NULL);
	i++;
	j = 0;
	while (old_buffer[i] != '\0')
		new_buffer[j++] = old_buffer[i++];
	new_buffer[j] = '\0';
	free(old_buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*line_temp;
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line_temp = ft_line(buffer[fd]);
	buffer[fd] = ft_skip(buffer[fd]);
	return (line_temp);
}

#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	int fd;
	fd = open("filr.txt", O_RDONLY);
	int fd1;
	fd1 = open("filr1.txt", O_RDONLY);
	int fd2;
	fd2 = open("filr2.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	while ((line = get_next_line(fd1)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	while ((line = get_next_line(fd2)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd2);
	return (0);
}