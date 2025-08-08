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
		tex_x = r->tex_x;
		if (r->side == 0)
		{
			if (r->dir.x > 0)
				tex_x += off;
			else
				tex_x -= off;
		}
		else
		{
			if (r->dir.y > 0)
				tex_x += off;
			else
				tex_x -= off;
		}
		if (tex_x < 0 || tex_x >= t->width)
			return (-1);
		return (get_texture_color(t, tex_x, tex_y));
	}
	return (get_texture_color(t, r->tex_x, tex_y));
}

static int	bg_cast_until_wall(t_game *g, t_ray *r)
{
	while (1)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if ((int)r->map.y < 0 || (int)r->map.y >= g->map.height
			|| (int)r->map.x < 0 || (int)r->map.x >= (int)ft_strlen(
				g->map.grid[(int)r->map.y]))
			return (0);
		if (g->map.grid[(int)r->map.y][(int)r->map.x] == '1')
			return (1);
		/* skip doors and empty space */
	}
}

static int	background_color_at(t_game *g, int x, int y)
{
	t_ray		r;
	t_texture	*tx;
	double		step;
	double		pos;
	int			tex_y;
	int			col;

	init_ray(g, &r, x);
	calculate_step_and_side_dist(g, &r);
	if (!bg_cast_until_wall(g, &r))
		return (y < g->mlx.current_height / 2)
			? g->map.ceiling_color : g->map.floor_color;
	calculate_perp_wall_dist(g, &r);
	calculate_line_height_and_draw_range(g, &r);
	if (y < r.draw_start)
		return (g->map.ceiling_color);
	if (y > r.draw_end)
		return (g->map.floor_color);
	tx = get_wall_texture(g, &r);
	calculate_wall_texture_coords(g, &r, tx);
	step = 1.0 * tx->height / r.line_height;
	pos = (y - r.draw_start) * step;
	tex_y = (int)pos & (tx->height - 1);
	col = get_texture_color(tx, r.tex_x, tex_y);
	if (r.side == 1)
		col = (col >> 1) & 8355711;
	return (col);
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
	if (color < 0)
	{
		color = background_color_at(game, x, y);
		put_pixel(game, x, y, color);
		return ;
	}
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
