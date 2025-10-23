/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:05:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/23 14:53:43 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	handle_color_change(int key, t_environment *env)
{
	if (key == 48 || key == 50)
		env->is_color_terrain = 0;
	if (key == 48)
		env->colors[0] = 0x606060;
	if (key == 48)
		env->colors[1] = 0xeaeaea;
	if (key == 49)
	{
		env->colors[0] = 0x51b1fc;
		env->colors[1] = 0xb9670c;
		env->colors[2] = 0xffa85a;
		env->is_color_terrain = 1;
	}
	if (key == 50)
	{
		env->colors[0] = 0x09090b;
		env->colors[1] = 0xeaeaea;
	}
	if (key == 51)
	{
		env->colors[0] = 0x17a7df;
		env->colors[1] = 0x7c9c3c;
		env->colors[2] = 0xf3c385;
		env->is_color_terrain = 1;
	}
}

static int	get_component(int value, int shift)
{
	return ((value >> shift) & 0xFF);
}

int	interpolate_color(int color1, int color2, double t)
{
	int		r;
	int		g;
	int		b;

	r = get_component(color1, 16) + t
		* (get_component(color2, 16) - get_component(color1, 16));
	g = get_component(color1, 8) + t
		* (get_component(color2, 8) - get_component(color1, 8));
	b = get_component(color1, 0) + t
		* (get_component(color2, 0) - get_component(color1, 0));
	return ((r << 16) | (g << 8) | b);
}

unsigned int	get_terrain_color(int height, t_environment *env)
{
	double	t;
	int		color1;
	int		color2;

	color1 = env->colors[1];
	color2 = env->colors[2];
	if (env->highest_z != env->lowest_z)
		t = (double)(height - env->lowest_z)
			/ (env->highest_z - env->lowest_z);
	else
		t = 0.0;
	if (height < 0)
	{
		color1 = env->colors[0];
		color2 = env->colors[1];
	}
	t = ft_norm(t);
	return (interpolate_color(color1, color2, t));
}

unsigned int	get_color(int height, t_environment *env)
{
	t_gradient_args	g;

	if (env->is_color_terrain)
		return (get_terrain_color(height, env));
	g.start_rgb = env->colors[0];
	g.end_rgb = env->colors[1];
	if (env->highest_z != env->lowest_z)
		g.normalized_z_t = (double)(height - env->lowest_z)
			/ (env->highest_z - env->lowest_z);
	else
		g.normalized_z_t = 0.0;
	g.normalized_z_t = ft_norm(g.normalized_z_t);
	return (interpolate_color(g.start_rgb, g.end_rgb, g.normalized_z_t));
}
