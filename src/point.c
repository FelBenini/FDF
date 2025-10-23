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

#include "fdf.h"

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
	t_3dpoint	*res;
	static int	count;

	res = (t_3dpoint *)malloc(sizeof(t_3dpoint));
	res->x = coords[X];
	res->y = coords[Y];
	res->z = coords[Z];
	if (color)
	{
		color += 3;
		res->color = ft_strdup(color);
		ft_strupcase(res->color);
	}
	else
		res->color = NULL;
	get_highest_projections(res, env);
	count++;
	ft_printf("\r⏏️  %d Map points parsed.", count);
	return (res);
}
