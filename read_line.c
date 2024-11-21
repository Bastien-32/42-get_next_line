/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:04:01 by badal-la          #+#    #+#             */
/*   Updated: 2024/11/21 15:03:12 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lensrc;

	i = 0;
	lensrc = 0;
	while (src[lensrc])
		lensrc++;
	if (size == 0)
		return (lensrc);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lensrc);
}

char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*dest;

	slen = 0;
	while (s[slen])
		slen++;
	dest = (char *)malloc((slen + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, slen + 1);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*content_buffer;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	content_buffer = ft_strdup(buffer);
	if (!content_buffer)
		return (NULL);
	return (content_buffer);
}

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd1;
	char	*dest;
	
	fd1 = open("fd.txt", O_RDONLY);
	if (fd1 < 0)
		return (write(1, "error", 1));
	dest = get_next_line(fd1);
	printf("%s", dest);
	free(dest);
	close(fd1);
}

