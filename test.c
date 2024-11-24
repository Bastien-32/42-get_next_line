#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	dest = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (free(s1), NULL);
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (free(s1), dest);
}

int	bn_in_str(char *str, char bn)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == bn)
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
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
	{
		if (str)
			free(str);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read != 0 && bn_in_str(str, '\n') == -1)
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

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	static char	*str;
	int			fd1;
	
	fd1 = open("fd.txt", O_RDONLY);
	if (fd1 < 0)
		return (write(1, "error", 1));
	str = search_bsn_and_stash(fd1, str);
	printf("%s", str);
	free(str);
	close(fd1);
}