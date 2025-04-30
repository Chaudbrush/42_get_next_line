/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:22:49 by vloureir          #+#    #+#             */
/*   Updated: 2025/04/28 08:34:05 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

t_list	*ft_lstnew(void *data);
void	ft_lstadd_back(t_list **lst, t_list *node);
void	ft_save_end(t_list **lst);
int		check_newline(char *str);
void	read_and_store(t_list **lst, char *buffer, int fd);
int		get_line_len(t_list *lst);
char	*create_line(t_list *lst, int len);
void	ft_init_list(t_list **lst, char *buffer);
char	*get_next_line(int fd);
void	ft_lstclear(t_list **lst);

#endif
