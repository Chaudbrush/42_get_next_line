/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:16:14 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/01 21:55:38 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}				t_list;

#define BUFFER_SIZE 3

char	*ft_strdup(const char *s);
int	ft_strlen(char *str);
void	ft_print_list(t_list *lst);

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
//	printf("lstnew: %ld\n", sizeof(t_list));
	new->data = ft_strdup((const char *)content);
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list *ptr;

	if (!lst)
		return NULL;
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return	;
	}
	else
	{
		end = ft_lstlast(*lst);
		end->next = new;
	}
}

void	ft_clean_alloc(t_list *lst)
{
	t_list	*ptr;

	if (!lst)
		return ;
	ptr = lst;
	while (ptr)
	{
		lst = ptr->next;
		free(ptr->data);
		free(ptr);
		ptr = lst;
	}
}

void	ft_lstcat(t_list *lst, char *str)
{
	int		i;
	int		j;
	t_list	*ptr;

	j = 0;
	ptr = lst;
	while (ptr)
	{
		i = 0;
		while (ptr->data[i])
		{
			str[j] = ptr->data[i];
			i++;
			j++;
		}
		ptr = ptr->next;
	}
	str[j] = '\0';
//	printf("%p\n", str);
	return ;
}

int	ft_lstlen(t_list *lst)
{
	int		i;
	int		len;
	t_list	*ptr;

	len = 0;
	ptr = lst;
	while (ptr)
	{
		i = 0;
		while (ptr->data[i])
		{
			i++;
			len++;
		}
		ptr = ptr->next;
	}
	return (len);
}

char	*ft_lst_to_str(t_list *lst)
{
	int		len;
	char	*str;

	len = ft_lstlen(lst);
	str = malloc(sizeof(char) * (len + 1));
//	printf("lst_to_str: %ld\n", sizeof(char) * (len + 1));
	if (!str)
		return NULL;
	ft_lstcat(lst, str);
//	printf("%p\n", str);
	return (str);
}

char	*get_next_line(int fd)
{
	int		i;
	char	buffer[BUFFER_SIZE];
	t_list	*new;
	t_list	*root;
	char	*string;
	int		n;

	root = NULL;
	string = NULL;
	buffer[BUFFER_SIZE] = '\0';
	while (i)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		new = ft_lstnew(buffer);
		ft_lstadd_back(&root, new);
		if (!i)
			break;
	}
	string = ft_lst_to_str(root);
//	printf("%p\n", string);
	ft_clean_alloc(root);
	return (string);
}
int	main(void)
{
	int		fd;
	char	*string;

	fd = open("test.txt", O_RDONLY | O_CREAT);
	string = get_next_line(fd);
	printf("%s\n", string);
	free(string);
	close(fd);
}

void	ft_print_list(t_list *lst)
{
	t_list	*ptr;

	ptr = lst;
	while(ptr)
	{
		printf("%s-> ", ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*string;

	len = ft_strlen((char *)s);
	if (!len)
		return NULL;
	string = malloc(sizeof(char) * (len + 1));
//	printf("strdup: %ld\n", sizeof(char) * (len + 1));
	if (!string)
		return NULL;
	i = -1;
	while (s[++i])
		string[i] = s[i];
	string[i] = '\0';
	printf("%s", string);
	return (string);
}

