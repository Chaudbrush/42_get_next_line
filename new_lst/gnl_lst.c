/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:55:33 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/28 08:21:52 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include "get_next_line.h"

#define BUFFER_SIZE 5

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

t_list	*ft_lstnew(void *data)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = data;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **lst, t_list *node)
{
	t_list	*ptr;

	if (!lst || !node)
		return ;
	if (!*lst)
		*lst = node;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*ptr;

	if (!lst)
		return ;
	while (*lst)
	{
		ptr = *lst;
		*lst = (*lst)->next;
		free(ptr->content);
		free(ptr);
	}
}

void	ft_save_end(t_list **lst)
{
	int		i;
	int		j;
	t_list	*ptr;

	if (!lst)
		return ;
	i = 0;
	j = 0;
	while ((*lst)->next)
	{
		ptr = *lst;
		*lst = (*lst)->next;
		free(ptr->content);
		free(ptr);
	}
	ptr = *lst;
	while ((ptr->content)[i] && (ptr->content)[i] != '\n')
		i++;
	if ((ptr->content)[i] == '\n')
		i++;
	while((ptr->content)[i])
		(ptr->content)[j++] = (ptr->content)[i++];
	(ptr->content)[j] = 0;
}

int	check_newline(char *str)
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

void	read_and_store(t_list **lst, char *buffer, int fd)
{
	int		state;
	int		bytes_read;
	t_list	*node;

	state = 1;
	bytes_read = 0;
	while (state)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (ft_lstclear(lst));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = 0;
		if (check_newline(buffer))
			state = 0;
		if (buffer[0])
		{
			node = ft_lstnew(buffer);
			ft_lstadd_back(lst, node);
		}
		if (bytes_read < 1)
			break ;
	}
}

int	get_line_len(t_list *lst)
{
	int		i;
	int		len;
	t_list	*ptr;

	if (!lst)
		return (0);
	len = 0;
	ptr = lst;
	while (ptr)
	{
		i = 0;
		while ((ptr->content)[i] && (ptr->content)[i] != '\n')
		{
			i++;
			len++;
		}
		if ((ptr->content)[i] == '\n')
			len++;
		ptr = ptr->next;
	}
	return (len);
}

char	*create_line(t_list *lst, int len)
{
	int		i;
	int		j;
	char	*tmp;
	t_list	*ptr;

	if (!len || !lst)
		return (NULL);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	ptr = lst;
	while (ptr)
	{
		i = 0;
		while ((ptr->content)[i] && (ptr->content)[i] != '\n')
			tmp[j++] = (ptr->content)[i++];
		if ((ptr->content)[i] == '\n')
			tmp[j++] = (ptr->content)[i++];
		ptr = ptr->next;
	}
	tmp[j] = 0;
	return (tmp);
}

size_t	ft_strlen(char *str)
{
	int	i;

	while (str[i])
		i++;
	return (i);
}

void	ft_init_list(t_list **lst, char *buffer)
{
	int		i;
	char	*tmp;
	t_list	*node;

	tmp = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (!tmp)
		return ;
	i = -1;
	while (buffer[++i])
		tmp[i] = buffer[i];
	tmp[i] = 0;
//	printf("tmp :[%s]\n", tmp);
	node = ft_lstnew(tmp);
	ft_lstadd_back(lst, node);
}

char	*get_next_line(int fd)
{
	static char	store[BUFFER_SIZE + 1];
	t_list		*lst;
	char		*buffer;
	int			len;
	int			i;

	lst = NULL;
	i = -1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
//	printf("%s", store);
	if (store[0])
		ft_init_list(&lst, store);
	read_and_store(&lst, buffer, fd);
	len = get_line_len(lst);
//	printf("len: %d\n", len);
	buffer = create_line(lst, len);
//	ft_lstclear(&lst);
	ft_save_end(&lst); 
	while ((lst->content)[++i])
		store[i] = (lst->content)[i];
	store[i] = 0;
	free(lst->content);
	free(lst);
//	printf("[%s]", store);
	return (buffer);
}

int	main(void)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i < 20)
	{
		line = get_next_line(fd);
//		printf("line %d: ", i);
		printf("%s", line);
		free(line);
		i++;
	}
}
