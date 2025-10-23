/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:51:51 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/07 15:15:16 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"

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
	int		x;
	int		y;
	int		z;
	char	*color;
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

typedef struct s_environment
{
	t_img_data		img;
	t_mlx_args		mlx;
	t_3dpoint		***map;
	int				highest_x;
	int				lowest_x;
	int				highest_y;
	int				lowest_y;
	int				highest_z;
	int				lowest_z;
	double			scale;
	int				offset_x;
	int				offset_y;
	unsigned int	colors[3];
}	t_environment;

typedef struct s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_rgb;

typedef struct s_gradient_args
{
	double			normalized_z_t;
	double			segment_t;
	t_rgb			start_rgb;
	t_rgb			end_rgb;
}	t_gradient_args;

void			draw_pixel(t_img_data *data, int x, int y, unsigned int color);
void			draw_line(t_img_data *data, t_2dpoint *from,
					t_2dpoint *to, int start);

t_2dpoint		*new_2dpoint(int x, int y, int z);
t_3dpoint		*new_3dpoint(int *coords, char *color, t_environment *env);
t_2dpoint		*isometric_projection(t_3dpoint *point3d, t_environment	*env);

int				close_window(void *params);
int				handle_keymaps(int keycode, void *params);

t_3dpoint		***parse_map(char *filename, t_environment *env);

t_environment	*init_environment(char *filename);
void			get_highest_projections(t_3dpoint *point_3d,
					t_environment *env);

void			clean_env(t_environment *env);
void			clear_splitted(char **splitted);

unsigned int	get_color(int height, t_environment *env);
t_rgb			create_rgba(unsigned int color);
unsigned int	interpolate_rgba(t_rgb start_comp, t_rgb end_comp,
					double t);
t_rgb			create_rgba(unsigned int color);

int				validate_input(char *filename);

#endif
