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

int	main(int argc, char **argv)
{
	int		i;
	int		fd1;
	int		fd2;
	char	*line;

	if (argc == 3)
	{
		i = 1;
		fd1 = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_RDONLY);
		while (i <= 25)
		{
			if (i % 2)
				line = get_next_line(fd1);
			else
				line = get_next_line(fd2);
			printf("line %d: ", i);
			printf("%s", line);
			free(line);
			i++;
		}
		close(fd1);
		close(fd2);
	}
	return (0);
}
