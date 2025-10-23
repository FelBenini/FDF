/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:00:59 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/23 15:00:37 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	rotate_x_axis(double *y, double *z, double x_cos, double x_sin)
{
	double	temp_y;
	double	temp_z;

	temp_y = *y;
	temp_z = *z;
	*y = temp_y * x_cos - temp_z * x_sin;
	*z = temp_y * x_sin + temp_z * x_cos;
}

static void	rotate_y_axis(double *x, double *z, double y_cos, double y_sin)
{
	double	temp_x;
	double	temp_z;

	temp_x = *x;
	temp_z = *z;
	*x = temp_x * y_cos + temp_z * y_sin;
	*z = -temp_x * y_sin + temp_z * y_cos;
}

static void	rotate_z_axis(double *x, double *y, double z_cos, double z_sin)
{
	double	temp_x;
	double	temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = temp_x * z_cos - temp_y * z_sin;
	*y = temp_x * z_sin + temp_y * z_cos;
}

static void	bend_axis(double x, double y, double *z, t_environment *env)
{
	double	factor;
	double	curve_factor;

	factor = x + y;
	factor *= 0.1;
	factor *= M_PI;
	curve_factor = sin(factor);
	curve_factor *= env->bending_factor;
	*z += -curve_factor;
}

t_2dpoint	project_point(t_3dpoint *point3d, t_environment *env)
{
	double	coords[3];

	coords[X] = point3d->x;
	coords[Y] = point3d->y;
	coords[Z] = -point3d->z * env->z_factor;
	bend_axis(coords[X], coords[Y], &coords[Z], env);
	rotate_x_axis(&coords[Y], &coords[Z], env->camera.x_cos, env->camera.x_sin);
	rotate_y_axis(&coords[X], &coords[Z], env->camera.y_cos, env->camera.y_sin);
	rotate_z_axis(&coords[X], &coords[Y], env->camera.z_cos, env->camera.z_sin);
	if (env->camera.projection == ISOMETRIC)
		return (isometric_projection(point3d, coords, env));
	else
		return (parallel_projection(point3d, env, coords[X], coords[Y]));
}
