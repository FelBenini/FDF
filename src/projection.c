/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:00:59 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/06 20:17:56 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_2dpoint	*isometric_projection(t_3dpoint *point3d, t_environment	*env)
{
	t_2dpoint		*res;
	double			projected_x;
	double			projected_y;

	res = (t_2dpoint *)malloc(sizeof(t_2dpoint));
	if (res == NULL)
		return (NULL);
	projected_x = -(point3d->x - point3d->y) * 0.866;
	projected_y = -(point3d->x + 2 * point3d->y + -(point3d->z * 0.5)) * 0.5;
	res->x = (int)(projected_x * env->scale);
	res->y = (int)(projected_y * env->scale);
	res->height = point3d->z;
	if (point3d->color)
		res->color = ft_atoi_base(point3d->color, "0123456789ABCDEF");
	else
		res->color = get_color(res->height, env);
	res->x += env->offset_x;
	res->y += env->offset_y;
	return (res);
}
