/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:57:53 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/07 16:57:47 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	close_window(void *params)
{
	t_mlx_args	*mlx;

	mlx = (t_mlx_args *)params;
	mlx_loop_end(mlx->mlx);
	ft_printf("\n👋 Leaving now, bye!\n");
	return (0);
}

static void	reset_perspective(t_environment *env,
							double x_angle, double y_angle)
{
	env->camera.offset_x = 0;
	env->camera.offset_y = 0;
	env->camera.y_rotation = y_angle;
	env->camera.x_rotation = x_angle;
}

static void	handle_numpad(int keycode, t_environment *env)
{
	if (keycode == 65438)
		env->bending_factor = 0;
	if (keycode == 65429)
		reset_perspective(env, 0, 0);
	if (keycode == 65430)
		reset_perspective(env, 0.73, 0);
	if (keycode == 65436)
		reset_perspective(env, 1.57, 0);
	if (keycode == 65437)
		reset_perspective(env, 0.73, -0.73);
	if (keycode == 65433)
		reset_perspective(env, 1.57, -0.73);
	if (keycode == 65435)
		reset_perspective(env, 1.57, -1.57);
	if (keycode == 65432)
		reset_perspective(env, 0.73, -1.57);
	if (keycode == 65431)
		reset_perspective(env, 0, -0.73);
	if (keycode == 65434)
		reset_perspective(env, 0, -1.57);
}

void	handle_projection_changes(int keycode, t_environment *env)
{
	if (keycode == 105)
	{
		reset_perspective(env, 0, 0);
		env->camera.projection = ISOMETRIC;
	}
	if (keycode == 112)
	{
		reset_perspective(env, 0, 0);
		env->camera.projection = PARALLEL;
	}
}

int	handle_keymaps(int keycode, void *params)
{
	t_environment	*env;

	env = (t_environment *)params;
	if (keycode == 65307)
	{
		mlx_loop_end(env->mlx.mlx);
		ft_printf("\n👋 Leaving now, bye!\n");
	}
	translate(keycode, env);
	handle_color_change(keycode, env);
	if (keycode == 98)
		env->bending_factor += 0.1;
	if (keycode == 118)
		env->bending_factor -= 0.1;
	if (keycode == 91)
		env->z_factor -= 0.01;
	if (keycode == 93)
		env->z_factor += 0.01;
	handle_numpad(keycode, env);
	handle_projection_changes(keycode, env);
	rotate(keycode, params);
	return (0);
}
