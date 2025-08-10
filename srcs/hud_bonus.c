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

	if (!game->weapon_tex.img)
		return ;
	start_x = (game->mlx.current_width - game->weapon_tex.width) / 2;
	start_y = game->mlx.current_height - game->weapon_tex.height;
	src_y = 0;
	while (src_y < game->weapon_tex.height)
	{
		draw_weapon_row(game, start_x, start_y, src_y);
		src_y++;
	}
}
