#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 7

int	ft_strlen(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int	check_newline(char *buffer);
char	*get_next_line(int fd);
void	ft_read_and_store(int fd, char **line, char *buffer);
void	clean_line(char **line);
void	clean_buffer(char *buffer);

int	check_newline(char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '\n')
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
//	line = malloc(sizeof(char));
//	if (!line)
//		return (NULL);
//	line[0] = '\0';
//	if (!check_newline(buffer))
	ft_read_and_store(fd, &line, buffer);
//	printf("line: [%s]\n", line);
//	printf("buffer: [%s]\n", buffer);
	if (line)
		clean_line(&line);
//	printf("line: [%s]\n", line);
	clean_buffer(buffer);
//	printf("buffer: [%s]\n", buffer);
	return (line);
// Stash can be the actual string that I'll send back
// The static function can be of the size of buffer + 1 (cause if can never be bigger than buffer itself)
//	return (NULL);
}
// Uses read() to read from the file and add characters to the stash

void	ft_read_and_store(int fd, char **line, char *buffer)
{
//	int		state;
	int		bytes_read;
//	char	*tmp;

//	state = 1;
	bytes_read = 0;
	if (buffer[0])
//	{
		*line = ft_strjoin(*line, buffer);
//		free(*line);
//		*line = tmp;
//	}
//	while (1)
	while (!check_newline(buffer))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
//		printf("read: %d\n", bytes_read);
		if (bytes_read < 1)
		{
//			free(*line);
//			*line = NULL;
			break ;
		}
		buffer[bytes_read] = '\0';
		*line = ft_strjoin(*line, buffer);
//		free(*line);
//		*line = tmp;
//		printf("%s\n", *line);
//		write(1, buffer, bytes_read);
//		if (check_newline(buffer))
//			break ;
	}
}

// Extracts all characters from our stash and stores in out line
// Stopping if you find a \n

void	clean_line(char **line)
{
//	int		i;
	int		len;
//	char	*tmp;

//	if (!line)
//		return ;
//	i = -1;
	len = 0;
//	tmp = NULL;
	while ((*line)[len])
	{
		if ((*line)[len] == '\n')
		{
			len++;
			break ;
		}
		len++;
	}
	(*line)[len] = '\0';
}

void	clean_buffer(char *buffer)
{
	int	i;
	int	j;

//	if (!buffer)
//		return ;
	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i = i + 1;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
//    printf("%s\n", buffer);
}

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*line;

	if (argc == 2)
	{
		i = 1;
		fd = open(argv[1], O_RDONLY);
		while (i <= 25)
		{
			line = get_next_line(fd);
			printf("line %d: ", i);
			printf("%s", line);
			free(line);
			i++;
		}
		close(fd);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	if (!s2[0])
		return (NULL);
	i = 0;
	j = 0;
	if (!s1)
		len = ft_strlen((char *)s2);
	else
		len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s1 && s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	free((char *)s1);
//	printf("new: %s\n", new);
	return (new);
}
