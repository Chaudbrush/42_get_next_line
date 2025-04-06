/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:34:54 by vloureir          #+#    #+#             */
/*   Updated: 2025/03/20 21:34:02 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 15

int	get_next_line(int fd, char **line);

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	line(void)
{
	int		fd;
	char	buffer[BUFFER_SIZE];

//	buffer[BUFFER_SIZE] = '\0';
//	ft_memset(buffer, 0, sizeof(buffer));
	fd = open("test.txt", O_RDONLY);

	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
//		printf("%s", buffer);
		write(1, buffer, BUFFER_SIZE);
//		ft_putstr(buffer);
	}
	close(fd);
}

int	full_file(void)
{
	int		fd;
	char	buffer[BUFFER_SIZE];

//	buffer[BUFFER_SIZE] = '\0';
//	ft_memset(buffer, 0, sizeof(buffer));
	fd = open("test.txt", O_RDONLY);

	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
//		printf("%s", buffer);
		write(1, buffer, BUFFER_SIZE);
//		ft_putstr(buffer);
	}
	close(fd);
}


int	main(void)
{
	line();
}
