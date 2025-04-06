/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:40:24 by vloureir          #+#    #+#             */
/*   Updated: 2025/03/22 19:00:11 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 3

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

char	*get_next_line(int fd)
{
	int		i;
	int		amount;
	char	buffer[4096];
	char	buff[BUFFER_SIZE + 1];

	i = 0;
	buff[BUFFER_SIZE] = 0;
	while (1)
	{
		amount = read(fd, buff, BUFFER_SIZE);
		if (amount == 0)
			break;
//		printf("%d\n", amount);
		ft_putstr(buff);
		ft_strlcpy(&buffer[i], buff, amount + 1);
//		ft_putstr(buffer);
		printf("i: %d\n", i);
		i += amount;
	}
	return (buffer);
}

int	main(int argc, char **argv)
{
	int	fd;

//	if (argc < 2)
//		return (1);
	fd = open("test.txt", O_RDONLY);
//	get_next_line(fd);
	ft_putstr(get_next_line(fd));

	close (fd);
	return (0);
}
