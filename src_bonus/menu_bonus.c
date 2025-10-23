/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:44:49 by fbenini-          #+#    #+#             */
/*   Updated: 2025/09/18 19:56:13 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	fill_color(t_img_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y <= img->height)
	{
		x = 0;
		while (x <= img->width)
		{
			draw_pixel(img, x, y, 0x343434);
			x++;
		}
		y++;
	}
}

static void	put_str(int y, int x, char *str, t_environment *env)
{
	mlx_string_put(env->mlx.mlx, env->mlx.win,
		x, y, 0xFFFFFFFF, str);
}

static void	put_banner(t_environment *env)
{
	int	start;
	int	r;

	start = 32;
	r = 1700;
	put_str(start, r, "  .-.          ___    .-.", env);
	put_str(start + 12, r, " /    \\       (   )  /    \\ ", env);
	put_str(start + 24, r, " | .`. ;    .-.| |   | .`. ;  ", env);
	put_str(start + 36, r, " | |(___)  /   \\ |   | |(___) ", env);
	put_str(start + 48, r, " | |_     |  .-. |   | |_     ", env);
	put_str(start + 60, r, "(   __)   | |  | |  (   __)   ", env);
	put_str(start + 72, r, " | |      | |  | |   | |      ", env);
	put_str(start + 84, r, " | |      | |  | |   | |      ", env);
	put_str(start + 96, r, " | |      | '  | |   | |      ", env);
	put_str(start + 108, r, " | |      ' `-'  /   | |      ", env);
	put_str(start + 120, r, "(___)      `.__,'   (___)     ", env);
}

static void	print_numpad(t_environment *env)
{
	put_str(552, 167, "0 NUMPAD:       RESET WAVY EFFECT", env);
	put_str(572, 1672, "1 NUMPAD:       VIEWING FROM Y ANGLE", env);
	put_str(592, 1672, "2 NUMPAD:       BETWEEN Y & X ANGLE", env);
	put_str(612, 1672, "3 NUMPAD:       VIEWING FROM X ANGLE", env);
	put_str(632, 1672, "4 NUMPAD:       BETWEEN TOP & Y ANGLE", env);
	put_str(652, 1672, "5 NUMPAD:       ISOMETRIC PROJECTION", env);
	put_str(672, 1672, "6 NUMPAD:       SIDELINES DIAGONAL", env);
	put_str(692, 1672, "7 NUMPAD:       PARALLEL PROJECTION", env);
	put_str(712, 1672, "8 NUMPAD:       BETWEEN PARALLEL & ISO", env);
	put_str(732, 1672, "9 NUMPAD:       PARALLEL FROM THE SIDE", env);
}

void	print_menu(t_environment *env)
{
	fill_color(&env->menu);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.win,
		env->menu.img, 1920 - env->menu.width, 0);
	put_banner(env);
	put_str(188, 1672, "_______________COLORS________________", env);
	put_str(212, 1678, "0. DEFAULT", env);
	put_str(232, 1678, "1. TERRAIN", env);
	put_str(212, 1798, "2. VOID", env);
	put_str(232, 1798, "3. LAND", env);
	put_str(300, 1672, "______________CONTROLS_______________", env);
	put_str(332, 1672, "ARROW KEYS:      ROTATE", env);
	put_str(362, 1672, "WASD:            MOVE MODEL", env);
	put_str(392, 1672, "V AND B KEYS:    APPLY WAVY EFFECT", env);
	put_str(422, 1672, "MOUSE SCROLL:    ZOOM IN AND OUT", env);
	put_str(452, 1672, "[ AND ] KEYS:    MODIFY HEIGHT", env);
	put_str(522, 1672, "___________NUMPAD_CONTROLS___________", env);
	print_numpad(env);
	put_str(772, 1672, "___________MOUSE__CONTROLS___________", env);
	put_str(812, 1672, "- HOLD SCROLL AND MOVE TO ROTATE MODEL", env);
	put_str(832, 1672, "- HOLD RIGHT CLICK AND MOVE THE MOUSE TO", env);
	put_str(848, 1672, "TO TRANSLATE THE MODEL", env);
	put_str(888, 1672, "_____________PROJECTIONS____________", env);
	put_str(1008, 1672, "I. ISOMETRIC           P. PARALLEL", env);
}
