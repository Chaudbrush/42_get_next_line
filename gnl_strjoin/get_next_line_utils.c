/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:22:05 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/24 10:22:28 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*new;

	if (!s2[0])
		return (NULL);
	i = 0;
	j = 0;
	if (!s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
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
	return (new);
}

void	ft_read_and_store(int fd, char **line, char *buffer)
{
	int		bytes_read;

	bytes_read = 0;
	if (buffer[0])
		*line = ft_strjoin(*line, buffer);
	while (!check_newline(buffer))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 1)
			break ;
		buffer[bytes_read] = '\0';
		*line = ft_strjoin(*line, buffer);
	}
}

void	clean_line(char **line)
{
	int		len;

	if (!*line)
		return ;
	len = 0;
	while ((*line)[len] && (*line)[len] != '\n')
		len++;
	if ((*line)[len] == '\n')
		len++;
	(*line)[len] = '\0';
}

void	clean_buffer(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}
