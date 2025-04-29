/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:21:32 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/28 08:33:10 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	read_and_store(t_list **lst, char *buffer, int fd)
{
	int		state;
	int		bytes_read;
	t_list	*node;

	state = 1;
	bytes_read = 0;
	node = NULL;
	while (state)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (ft_lstclear(lst));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = 0;
		if (check_newline(buffer))
			state = 0;
		node = ft_lstnew(buffer);
		ft_lstadd_back(lst, node);
		if (bytes_read < 1)
			break ;
	}
}

void	ft_init_list(t_list **lst, char *buffer)
{
	int		i;
	int		len;
	char	*tmp;
	t_list	*node;

	len = 0;
	while (buffer[len])
		len++;
	tmp = malloc(sizeof(char) * (len + 1));
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

	buffer = NULL;
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
