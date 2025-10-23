/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:53:49 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/15 19:47:35 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static t_3dpoint	*create_point(int j, int i, char *str,
								t_environment *env)
{
	int			coords[3];
	t_3dpoint	*res;
	char		*color;

	coords[X] = j - 1;
	coords[Y] = i;
	coords[Z] = ft_atoi(str);
	color = ft_strnstr(str, "0x", 30);
	res = new_3dpoint(coords, color, env);
	return (res);
}

static t_3dpoint	***convert_list_to_matrix(t_list *head,
											unsigned int lst_size,
											t_environment *env)
{
	t_3dpoint		***res;
	unsigned int	i;
	unsigned int	j;
	char			**content;

	i = 0;
	res = (t_3dpoint ***)malloc((lst_size + 1) * sizeof(t_3dpoint **));
	while (head)
	{
		j = 0;
		content = (char **)head->content;
		while (content[j])
			j++;
		res[i] = (t_3dpoint **)malloc((j + 1) * sizeof(t_3dpoint *));
		j = 0;
		while (content[j++])
			res[i][j - 1] = create_point(j, i, content[j - 1], env);
		res[i][j - 1] = 0;
		head = head->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

void	get_dimensions(t_3dpoint ***matrix, t_environment *env)
{
	int				x;
	int				y;

	y = 0;
	x = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
			x++;
		y++;
	}
	env->width = x;
	env->height = y;
}

t_3dpoint	***parse_map(t_list **head, t_environment *env)
{
	t_3dpoint	***res;

	res = convert_list_to_matrix(*head, ft_lstsize(*head), env);
	ft_lstclear(head, clear_splitted);
	return (res);
}
