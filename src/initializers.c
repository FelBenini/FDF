/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:33:51 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/07 20:22:02 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_highest_point(t_3dpoint ***map, t_environment **environment)
{
	int				i;
	int				j;
	t_environment	*env;

	i = 0;
	env = *environment;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j]->z > env->highest_z)
				env->highest_z = map[i][j]->z;
			if (map[i][j]-> z < env->lowest_z)
				env->lowest_z = map[i][j]->z;
			j++;
		}
		i++;
	}
}

void	get_highest_projections(t_3dpoint *point_3d, t_environment *env)
{
	t_2dpoint		*point_2d;

	point_2d = isometric_projection(point_3d, env);
	if (env->highest_x < point_2d->x)
		env->highest_x = point_2d->x;
	if (env->lowest_x > point_2d->x)
		env->lowest_x = point_2d->x;
	if (env->highest_y > point_2d->y)
		env->highest_y = point_2d->y;
	if (env->lowest_y < point_2d->y)
		env->lowest_y = point_2d->y;
	free(point_2d);
}

static t_environment	*start_env(void)
{
	t_environment	*env;

	env = malloc(sizeof(t_environment));
	env->highest_x = 0;
	env->lowest_x = 0;
	env->highest_y = 0;
	env->lowest_y = 0;
	env->highest_z = 0;
	env->lowest_z = 0;
	env->offset_x = 0;
	env->offset_y = 0;
	env->colors[0] = 0x646464;
	env->colors[1] = 0xD4D4D4;
	env->colors[2] = 0xFFFFFF;
	env->scale = 1.5;
	if (!env)
		return (NULL);
	return (env);
}

t_environment	*init_environment(char *filename)
{
	t_environment	*env;
	char			*title;

	env = start_env();
	if (!env)
		return (NULL);
	env->map = parse_map(filename, env);
	env->img.width = 1920;
	env->img.height = 1080;
	env->mlx.mlx = mlx_init();
	title = ft_strjoin("FDF - ", filename);
	env->mlx.win = mlx_new_window(env->mlx.mlx, env->img.width,
			env->img.height, title);
	env->img.img = mlx_new_image(env->mlx.mlx, env->img.width, env->img.height);
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel,
			&env->img.line_length, &env->img.endian);
	get_highest_point(env->map, &env);
	if (env->highest_x - env->lowest_x < env->highest_y - env->lowest_y)
		env->scale = (1920 * 0.80) / (env->highest_x - env->lowest_x);
	else
		env->scale = (1580 * 0.85) / (env->highest_y - env->lowest_y);
	env->offset_x = (1320 - ((env->highest_x) * env->scale)) / 2;
	env->offset_y = (1490 - ((env->highest_y) * env->scale)) / 2;
	free(title);
	return (env);
}
