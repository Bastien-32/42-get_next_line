/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:04:01 by badal-la          #+#    #+#             */
/*   Updated: 2024/11/22 11:57:41 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	dest = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	free((char *)s1);
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) || (len > ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (((unsigned char *)s)[start + i] && i < len)
	{
		dest[i] = ((unsigned char *)s)[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*search_bsn_and_stash(int fd)
{
	ssize_t		bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	char		*str;
	
	while (bytes_read > 0 || ft_strchr(buffer, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		str = ft_strjoin(str, buffer);
	}
	return (str);
}

char	*ft_write_line(char *str)
{
	int		len;
	char	*dest;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	dest = ft_substr(str, 0, len);
	if (str[len] == '\n')
		dest[len + 1] = '\n';
	free(str);
	return (dest);
}

char	*ft_after_bsn(char *str)
{
	int		len;
	char	*dest;
	int		i;

	len = 0;
	i = 0;
	while (str[len] != '\n')
		len++;
	while (str[len + i + 1])
		i++;
	dest = ft_substr(str, len + 1, i);
	free(str);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*content_buffer;
	char		*line_return;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	content_buffer = search_bsn_and_stash(fd);
	if (!content_buffer)
		return (NULL);
	line_return = ft_write_line(content_buffer);// mettre dans la fct la boucle while (en commentaire dans search_bsn_and_stash) pour retourner la phrase 
	content_buffer = ft_after_bsn(content_buffer);//stocker le contenu apres \n dans content_buffer
	return (line_return);
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

