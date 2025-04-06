/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:16:14 by vloureir          #+#    #+#             */
/*   Updated: 2025/03/30 22:13:59 by vloureir         ###   ########.fr       */
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

#define BUFFER_SIZE 5

char	*ft_strdup(const char *s);
int	ft_strlen(char *str);
void	ft_print_list(t_list *lst);

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	printf("lstnew: %ld\n", sizeof(t_list));
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
/*
t_list	*get_next_line(int fd)
{
//	char	buff[BUFFER_SIZE];
	int		i;
	t_list	*new;
	t_list	*root;
	char	*buffer[] = {"hello ", "this ", "is ", "a very ", "nice ", "string"};

	i = 0;
	root = NULL;
	while (i < 6)
	{
		new = ft_lstnew(buffer[i]);
		ft_lstadd_back(&root, new);
		i++;
	}
	return (root);
}
*/

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
	printf("%p\n", str);
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

void	ft_lst_to_str(t_list *lst, char *str)
{
	int		len;
	char	*str;

	len = ft_lstlen(lst);
	str = malloc(sizeof(char) * (len + 1));
	printf("lst_to_str: %ld\n", sizeof(char) * (len + 1));
	if (!str)
		return ;
	str = ft_lstcat(lst, str);
	printf("%p\n", str);
}

char	*get_next_line(void)
{
//	char	buff[BUFFER_SIZE];
	int		i;
	t_list	*new;
	t_list	*root;
	char	*buffer[] = {"abc", "def", "ghi", "jkl", "mnop"};
	char	*string;

	i = 0;
	root = NULL;
	string = NULL;
	while (i < 5)
	{
		new = ft_lstnew(buffer[i]);
		ft_lstadd_back(&root, new);
		i++;
	}
	string = ft_lst_to_str(root, string);
	printf("%p\n", string);
	ft_clean_alloc(root);
//	printf("%s\n", string);
	return (string);
}
/*
t_list	*get_next_line(int fd)
{
//	char	buff[BUFFER_SIZE];
	int		i;
	t_list	*new;
	t_list	*root;
//	char	*buff[] = {"hello ", "this ", "is ", "a very ", "nice ", "string"};
	char	*buffer[] = {"abc", "def", "ghi", "jkl", "mno", "pqr"};
	char	*string;

	i = 0;
	root = NULL;
	string = NULL;
	while (i < 6)
	{
		new = ft_lstnew(buffer[i]);
		ft_lstadd_back(&root, new);
		i++;
	}
	ft_lst_to_str(root, string);
	return (root);
}
*/
int	main(void)
{
//	int		fd;
//	t_list	*result;
	char	*string;

//	fd = open("test.txt", O_RDONLY | O_CREAT);
//	result = get_next_line(fd);
	string = get_next_line();
//	ft_print_list(result);
	printf("%p\n", string);
	free(string);
//	close(fd);
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
	printf("strdup: %ld\n", sizeof(char) * (len + 1));
	if (!string)
		return NULL;
	i = -1;
	while (s[++i])
		string[i] = s[i];
	string[i] = '\0';
	return (string);
}

