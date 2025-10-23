/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:05:33 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/06 20:25:19 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char	get_component(unsigned int color, int shift)
{
	return ((unsigned char)((color >> shift) & 0xFF));
}

unsigned int	interpolate_rgba(t_rgb start_comp, t_rgb end_comp,
									double t)
{
	t_rgb	res;

	res.r = (unsigned char)(start_comp.r + t
			* (end_comp.r - start_comp.r));
	res.g = (unsigned char)(start_comp.g + t
			* (end_comp.g - start_comp.g));
	res.b = (unsigned char)(start_comp.b + t
			* (end_comp.b - start_comp.b));
	return ((res.r << 16) | (res.g << 8) | res.b);
}

t_rgb	create_rgba(unsigned int color)
{
	t_rgb	res;

	res.r = get_component(color, 16);
	res.g = get_component(color, 8);
	res.b = get_component(color, 0);
	return (res);
}

unsigned int	get_color(int height, t_environment *env)
{
	t_gradient_args	g;

	g.start_rgb = create_rgba(env->colors[0]);
	g.end_rgb = create_rgba(env->colors[1]);
	if (env->highest_z != env->lowest_z)
		g.normalized_z_t = (double)(height - env->lowest_z)
			/ (env->highest_z - env->lowest_z);
	else
		g.normalized_z_t = 0.0;
	g.normalized_z_t = ft_norm(g.normalized_z_t);
	return (interpolate_rgba(g.start_rgb, g.end_rgb, g.normalized_z_t));
}
