/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ggline.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:24:26 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/06 19:25:22 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int	ft_strlen(char *str);
int	has_newline(char *str);
char	*ft_strcpy(char *dst, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *str);

//char	*buffer_to_string(char *str, char *buffer)
//
//TODO: create a function that will malloc strlen(string) + strelen(buffer) + 1
//Join both string, and free the memory from the string;

//char	*ft_clean_string(char *str)
//
//TODO: will read the string, until it finds a '\n' or a '\0'
// if finds a '\n', will get the len of the remaining data, and store in the string
// if finds a '\0', 

char	*buffer_to_string(char *str, char *buffer)
{
	char *new;

	new = ft_strjoin(str, buffer);
	free(str);
	return (new);
}

char	*ft_only_line(char *str)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_clean_string(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		tmp = ft_strdup(&str[i + 1]);
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	char		*string;
	char		buffer[BUFFER_SIZE + 1];
	static char	*acumulator;

	if (!acumulator)
	{
		acumulator = malloc(sizeof(char));
		if (!acumulator)
			return (NULL);
		acumulator[0] = '\0';
	}
	bytes_read = 0;
	buffer[BUFFER_SIZE + 1] = '\0';
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		acumulator = buffer_to_string(acumulator, buffer);
		if (!bytes_read || has_newline(buffer))
			break ;
	}
//	TODO:	Clean the acumulator
//			store the line in the string
//			store the data after the newline in the acumulatorV
	string = ft_only_line(acumulator);
	acumulator = ft_clean_string(acumulator);
//	printf("new: %s\n", string);
//	printf("old: %s\n", acumulator);
//	free(acumulator);
	return (string);
}

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*string;

	if (argc == 2)
	{
		i = 0;
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (1);
		while (i < 5)
		{
			string = get_next_line(fd);
			printf("%s\n", string);
			free(string);
			i++;
		}
		close(fd);
	}
	else
		return (1);
//	free(string);
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

int	has_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *ft_strcpy(char *dst, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	return (new);
}

char	*ft_strdup(char *str)
{
	int		i;
	int		len;
	char	*new;

	i = -1;
	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + 1));
	while (str[++i])
		new[i] = str[i];
	new[i] ='\0';
	return (new);
}
