/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:25:24 by badal-la          #+#    #+#             */
/*   Updated: 2024/11/25 16:52:30 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	pos_bsn_in_str(char *str, char bsn)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == bsn)
			return (i);
		i++;
	}
	return (-1);
}

char	*search_bsn_and_stash(int fd, char *str)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && pos_bsn_in_str(str, '\n') == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			if (str)
				free(str);
			return (free(buffer), NULL);
		}
		buffer[bytes_read] = '\0';
		str = ft_strjoin(str, buffer);
	}
	return (free(buffer), str);
}

char	*write_line(char *str, int i)
{
	char	*line;

	if (i == -1)
		line = ft_substr(str, 0, ft_strlen(str));
	else
		line = ft_substr(str, 0, i + 1);
	if (!line[0])
		return (free(line), NULL);
	return (line);
}

char	*stash_after_bsn(char *str, int i)
{
	char	*stash;

	if (!str[0] || i == -1)
		return (free(str), NULL);
	stash = ft_substr(str, i + 1, ft_strlen(str));
	free(str);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*str[10000];
	char		*line;
	int			i;

	str[fd] = search_bsn_and_stash(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	i = pos_bsn_in_str(str[fd], '\n');
	line = write_line(str[fd], i);
	str[fd] = stash_after_bsn(str[fd], i);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int	fd1;
	int fd2;
	char	*line;

	fd1 = open("fd1.txt", O_RDONLY);
	line = get_next_line(fd1);
	printf("%s", line);
	free(line);
	fd2 = open("fd2.txt", O_RDONLY);
	line = get_next_line(fd2);
	printf("%s", line);
	free(line);
	line = get_next_line(fd1);
	printf("%s", line);
	line = get_next_line(fd2);
	printf("%s", line);
	line = get_next_line(fd1);
	printf("%s", line);
	close(fd1);
	close(fd2);
	free(line);
}
*/
