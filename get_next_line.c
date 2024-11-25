/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:13:49 by badal-la          #+#    #+#             */
/*   Updated: 2024/11/25 12:45:03 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	buffer = NULL;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (free(str), NULL);
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
	if (line[0] == NULL)
		return (free(line), NULL);
	return (line);
}

char	*stash_content_after_bsn(char *str, int i)
{
	char	*stash;

	if (str[0] == NULL || i == -1)
		return (free(str), NULL);
	stash = ft_substr(str, i + 1, ft_strlen(str));
	free(str);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	int			i;

	str = search_bsn_and_stash(fd, str);
	if (!str)
		return (NULL);
	i = pos_bsn_in_str(str, '\n');
	line = write_line(str, i);
	str = stash_content_after_bsn(str, i);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	static char	*str;
	int			fd1;
	
	fd1 = open("fd.txt", O_RDONLY);
	if (fd1 < 0)
		return (write(1, "error", 1));
	str = get_next_line(fd1);
	printf("%s", str);
	str = get_next_line(fd1);
	printf("%s", str);
	free(str);
	close(fd1);
}
*/