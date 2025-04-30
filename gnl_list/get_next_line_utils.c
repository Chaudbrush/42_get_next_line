/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:27:11 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/28 08:37:40 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	ft_save_end(t_list **lst)
{
	int		i;
	int		j;
	t_list	*ptr;

	if (!lst || !*lst)
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
	while ((ptr->content)[i])
		(ptr->content)[j++] = (ptr->content)[i++];
	(ptr->content)[j] = 0;
}

int	check_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
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
	*lst = NULL;
}
