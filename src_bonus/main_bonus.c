/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:48:48 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/18 18:54:20 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <sys/time.h>

static void	set_background(t_img_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y <= img->height)
	{
		x = 0;
		while (x <= img->width)
		{
			draw_pixel(img, x, y, 0x09090b);
			x++;
		}
		y++;
	}
}

static int	count_line_size(t_3dpoint **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

static void	create_lines(t_3dpoint ***matrix, t_img_data *img_data,
						int i, t_environment *env)
{
	t_2dpoint	point;
	t_2dpoint	next_point;
	int			j;
	int			next_line_size;

	j = 0;
	next_line_size = 0;
	if (matrix[i + 1])
		next_line_size = count_line_size(matrix[i + 1]);
	while (matrix[i][j])
	{
		point = project_point(matrix[i][j], env);
		if (matrix[i][j + 1])
		{
			next_point = project_point(matrix[i][j + 1], env);
			draw_line(img_data, point, next_point, 0);
		}
		if (matrix[i + 1] && j < next_line_size)
		{
			next_point = project_point(matrix[i + 1][j], env);
			draw_line(img_data, point, next_point, 0);
		}
		j++;
	}
}

void	print_matrix(t_environment *env)
{
	static struct timeval	last_call_time = {0, 0};
	struct timeval			current_time;
	long long				time_diff;
	t_3dpoint				***matrix;
	int						i;

	gettimeofday(&current_time, NULL);
	time_diff = (current_time.tv_sec - last_call_time.tv_sec)
		* 1000000 + (current_time.tv_usec - last_call_time.tv_usec);
	if (time_diff >= env->total_map_points / 4.8)
	{
		i = 0;
		matrix = env->map;
		set_background(&env->img);
		while (matrix[i])
		{
			create_lines(matrix, &env->img, i, env);
			i++;
		}
		mlx_put_image_to_window(env->mlx.mlx, env->mlx.win,
			env->img.img, 0, 0);
		last_call_time = current_time;
	}
}

int	main(int argc, char *argv[])
{
	t_environment	*env;

	if (argc != 2)
		return (ft_printf("Please, pass a map as an input"), 1);
	env = init_environment(argv[1]);
	print_matrix(env);
	print_menu(env);
	mlx_mouse_get_pos(env->mlx.mlx, env->mlx.win,
		&env->keys.last_x, &env->keys.last_y);
	mlx_hook(env->mlx.win, 17, 0, close_window, &env->mlx);
	mlx_hook(env->mlx.win, 2, 1L << 0, handle_keymaps, env);
	mlx_hook(env->mlx.win, 4, 1L << 2, mouse_press, env);
	mlx_hook(env->mlx.win, 5, 1L << 3, mouse_drop, env);
	mlx_hook(env->mlx.win, 6, 1L << 6, mouse_move, env);
	mlx_loop_hook(env->mlx.mlx, loop_through_frames, env);
	mlx_loop(env->mlx.mlx);
	clean_env(env);
	return (0);
}
