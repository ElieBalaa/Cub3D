/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/10 12:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	put_pixel_if_visible(t_game *g, int x, int y, int color)
{
	if (x >= 0 && x < g->mlx.current_width && y >= 0
		&& y < g->mlx.current_height)
		put_pixel(g, x, y, color);
}

static void	draw_weapon_row(t_game *g, int start_x, int start_y, int src_y)
{
	int		src_x;
	int		dst_x;
	int		color;
	int		key;

	key = get_texture_color(&g->weapon_tex, 0, 0);
	src_x = 0;
	while (src_x < g->weapon_tex.width)
	{
		dst_x = start_x + src_x;
		color = get_texture_color(&g->weapon_tex, src_x, src_y);
		if (color != key)
			put_pixel_if_visible(g, dst_x, start_y + src_y, color);
		src_x++;
	}
}

void	draw_weapon_hud(t_game *game)
{
	int		start_x;
	int		start_y;
	int		src_y;
	int		off;
	t_texture	saved;
	t_texture	*cur;

	if (!game->weapon_tex.img)
		return ;
	saved = game->weapon_tex;
	cur = &saved;
	if (game->weapon_anim_phase != 0)
		cur = current_weapon_texture(game);
	off = cur->width / 10;
	start_x = (game->mlx.current_width - cur->width) / 2 + off + 15;
	start_y = game->mlx.current_height - cur->height;
	src_y = 0;
	while (src_y < cur->height)
	{
		game->weapon_tex = *cur;
		draw_weapon_row(game, start_x, start_y, src_y);
		src_y++;
	}
	game->weapon_tex = saved;
}

static int	nearby_door_cell(t_game *g)
{
	int		mx;
	int		my;
	int		dx;
	int		dy;

	mx = (int)(g->player.pos.x / MAP_SCALE);
	my = (int)(g->player.pos.y / MAP_SCALE);
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (my + dy >= 0 && my + dy < g->map.height && mx + dx >= 0
				&& mx + dx < (int)ft_strlen(g->map.grid[my + dy])
				&& g->map.grid[my + dy][mx + dx] == 'D')
				return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}

void	draw_press_e_hint(t_game *game)
{
	int		x;
	int		y;

	if (!nearby_door_cell(game))
		return ;
	x = (game->mlx.current_width / 2) - 140;
	y = game->mlx.current_height - 40;
	mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y,
		COLOR_WHITE, "Press E to open the Door");
}
