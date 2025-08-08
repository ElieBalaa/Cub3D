/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_wall_slice_ceiling(t_game *game, int x, int y)
{
	put_pixel(game, x, y, game->map.ceiling_color);
}

static int	compute_tex_y(t_game *g, t_ray *r, t_texture *t, int y)
{
	int	d;
	int	tex_y;

	d = y * 256 - g->mlx.current_height * 128 + r->line_height * 128;
	tex_y = ((d * t->height) / r->line_height) / 256;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= t->height)
		tex_y = t->height - 1;
	return (tex_y);
}

static int	sample_wall_color(t_game *g, t_ray *r, t_texture *t, int tex_y)
{
	int		tex_x;
	double	p;
	int		off;

	if (t == &g->door_tex)
	{
		p = g->door_prog[(int)r->map.y][(int)r->map.x];
		off = (int)(p * t->width);
		tex_x = (r->tex_x + off) % t->width;
		return (get_texture_color(t, tex_x, tex_y));
	}
	return (get_texture_color(t, r->tex_x, tex_y));
}

void	draw_wall_slice_wall(t_game *game, t_ray *ray, int x, int y)
{
	int			tex_y;
	int			color;
	t_texture	*texture;

	texture = get_wall_texture(game, ray);
	if (game->map.grid[(int)ray->map.y][(int)ray->map.x] == 'D')
		texture = &game->door_tex;
	tex_y = compute_tex_y(game, ray, texture, y);
	color = sample_wall_color(game, ray, texture, tex_y);
	if (ray->side == 1)
		color = (color >> 1) & 8355711;
	put_pixel(game, x, y, color);
}

void	draw_wall_slice(t_game *game, t_ray *ray, int x, t_texture *texture)
{
	int	y;

	(void)texture;
	y = 0;
	while (y < game->mlx.current_height)
	{
		if (y < ray->draw_start)
			draw_wall_slice_ceiling(game, x, y);
		else if (y >= ray->draw_start && y <= ray->draw_end)
			draw_wall_slice_wall(game, ray, x, y);
		else
			draw_floor_pixel(game, x, y);
		y++;
	}
}
