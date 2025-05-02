/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:56:23 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/29 18:44:02 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	test_gnl(int fd, char *str)
{
	char	*line;

	line = get_next_line(fd);
	printf("\nmine: %s", line);
	printf("test: %s", str);
	free(line);
}

int	main(void)
{
	int			i;
	int			fd;
	char		*temp;

	fd = open("read_error.txt", O_RDONLY);
	test_gnl(fd, "aaaaaaaaaa\n");
	test_gnl(fd, "bbbbbbbbbb\n");
	if (BUFFER_SIZE > 100)
	{
		while (temp != NULL)
		{
			temp = get_next_line(fd);
			free(temp);
		}
	}
	test_gnl(fd, NULL);
	close(fd);
	fd = open("read_error.txt", O_RDONLY);
	test_gnl(fd, "aaaaaaaaaa\n");
	test_gnl(fd, "bbbbbbbbbb\n");
	test_gnl(fd, "cccccccccc\n");
	test_gnl(fd, "dddddddddd\n");
	test_gnl(fd, NULL);
}
