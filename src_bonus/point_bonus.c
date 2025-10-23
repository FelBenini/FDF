/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:06:17 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/07 20:18:12 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_2dpoint	*new_2dpoint(int x, int y, int z)
{
	t_2dpoint	*res;

	res = (t_2dpoint *)malloc(sizeof(t_2dpoint));
	res->x = x;
	res->y = y;
	res->height = z;
	return (res);
}

t_3dpoint	*new_3dpoint(int *coords, char *color, t_environment *env)
{
	t_3dpoint		*res;
	static int		count;

	res = (t_3dpoint *)malloc(sizeof(t_3dpoint));
	res->x = coords[X];
	res->y = coords[Y];
	res->z = coords[Z];
	res->color = 0;
	res->has_color = 1;
	if (color)
	{
		color += 3;
		ft_strupcase(color);
		res->color = ft_atoi_base(color, "0123456789ABCDEF");
	}
	else
		res->has_color = 0;
	get_highest_projections(res, env);
	count++;
	env->total_map_points = count;
	return (res);
}

void	normalize_map(t_3dpoint ***map, t_environment *env)
{
	int				i;
	int				j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->y -= env->height / 2;
			map[i][j]->x -= env->width / 2;
			map[i][j]->y *= -1;
			map[i][j]->x *= -1;
			j++;
		}
		i++;
	}
}

void	normalize_frames(t_environment *env)
{
	t_list	*current;

	current = env->frames;
	while (current)
	{
		normalize_map(current->content, env);
		current = current->next;
	}
	env->total_map_points /= ft_lstsize(env->frames);
}
