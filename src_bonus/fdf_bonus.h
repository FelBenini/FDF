/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:51:51 by fbenini-          #+#    #+#             */
/*   Updated: 2025/10/07 16:17:49 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>

# define PARALLEL 0
# define ISOMETRIC 1

# define X 0
# define Y 1
# define Z 2

typedef struct s_mlx_args
{
	void	*win;
	void	*mlx;
}	t_mlx_args;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img_data;

typedef struct s_3dpoint
{
	int					x;
	int					y;
	int					z;
	int					color;
	int					has_color;
}	t_3dpoint;

typedef struct s_2dpoint
{
	int	x;
	int	y;
	int	height;
	int	color;
}	t_2dpoint;

typedef struct s_bresenham
{
	int	x;
	int	y;
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
	int	error;
	int	swapped;
	int	total_steps;
}	t_bresenham;

typedef struct s_camera
{
	double	x_cos;
	double	y_cos;
	double	z_cos;
	double	x_sin;
	double	y_sin;
	double	z_sin;
	double	y_rotation;
	double	x_rotation;
	double	z_rotation;
	int		offset_x;
	int		offset_y;
	int		projection;
}	t_camera;

typedef struct s_keys
{
	int	scroll_pressed;
	int	last_x;
	int	last_y;
	int	right_pressed;
}	t_keys;

typedef struct s_environment
{
	t_img_data		img;
	t_img_data		menu;
	t_mlx_args		mlx;
	t_camera		camera;
	t_list			*frames;
	t_3dpoint		***map;
	t_keys			keys;
	int				width;
	int				height;
	int				highest_x;
	int				lowest_x;
	int				highest_y;
	int				lowest_y;
	int				highest_z;
	int				lowest_z;
	double			scale;
	int				offset_x;
	int				offset_y;
	double			z_factor;
	unsigned int	colors[3];
	double			bending_factor;
	int				total_map_points;
	int				is_color_terrain;
}	t_environment;

typedef struct s_gradient_args
{
	double			normalized_z_t;
	double			segment_t;
	unsigned int	start_rgb;
	unsigned int	end_rgb;
}	t_gradient_args;

int				interpolate_color(int color1, int color2, double t);
void			draw_pixel(t_img_data *data, int x, int y, unsigned int color);
void			draw_line(t_img_data *data, t_2dpoint from,
					t_2dpoint to, int start);

t_2dpoint		*new_2dpoint(int x, int y, int z);
t_3dpoint		*new_3dpoint(int *coords, char *color, t_environment *env);
t_2dpoint		project_point(t_3dpoint *point3d, t_environment *env);
t_2dpoint		parallel_projection(t_3dpoint *point3d, t_environment *env,
					double x_val, double y_val);
t_2dpoint		isometric_projection(t_3dpoint *point3d, double *coords,
					t_environment *env);
t_2dpoint		curvilinear_projection(t_3dpoint *point3d, double x_val,
					double y_val, double z_val);
void			normalize_frames(t_environment *env);

int				close_window(void *params);
int				handle_keymaps(int keycode, void *params);
void			handle_color_change(int key, t_environment *env);

void			get_dimensions(t_3dpoint ***matrix, t_environment *env);
t_3dpoint		***parse_map(t_list **head, t_environment *env);

t_environment	*init_environment(char *filename);
void			get_highest_projections(t_3dpoint *point_3d,
					t_environment *env);
void			initialize_camera(t_environment *env);

void			clean_env(t_environment *env);
void			clear_splitted(void *splitted);
void			clear_matrix(void *ptr);

unsigned int	get_color(int height, t_environment *env);

t_list			*validate_input(int fd);

void			print_matrix(t_environment *env);

void			update_cos_sin(t_environment *env);
int				rotate(int keycode, void *params);
void			change_scale(int value, t_environment *env);
void			translate(int keycode, t_environment *env);

int				mouse_press(int key, int x, int y, void *param);
int				mouse_drop(int key, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);

void			print_menu(t_environment *env);

t_list			*parse_frames(char *directory_name, t_environment *env);
int				loop_through_frames(t_environment *env);

#endif
