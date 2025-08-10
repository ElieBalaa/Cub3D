/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 22:10:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 22:10:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	compute_wall_x(t_game *g, t_ray *r)
{
	double		w;

	if (r->side == 0)
		w = g->player.pos.y / MAP_SCALE + r->perp_wall_dist * r->dir.y;
	else
		w = g->player.pos.x / MAP_SCALE + r->perp_wall_dist * r->dir.x;
	return (w - floor(w));
}

static void	floor_wall_point(t_ray *r, double wall_x, double *fx, double *fy)
{
	if (r->side == 0 && r->dir.x > 0)
	{
		*fx = r->map.x;
		*fy = r->map.y + wall_x;
	}
	else if (r->side == 0 && r->dir.x < 0)
	{
		*fx = r->map.x + 1.0;
		*fy = r->map.y + wall_x;
	}
	else if (r->side == 1 && r->dir.y > 0)
	{
		*fx = r->map.x + wall_x;
		*fy = r->map.y;
	}
	else
	{
		*fx = r->map.x + wall_x;
		*fy = r->map.y + 1.0;
	}
}

static int	floor_tex_color(t_game *g, double cx, double cy)
{
	int			tx;
	int			ty;
	t_texture	*t;

	t = &g->floor_tex;
	if (!t->img || t->width <= 0 || t->height <= 0)
		return (g->map.floor_color);
	tx = ((int)(cx * t->width)) % t->width;
	ty = ((int)(cy * t->height)) % t->height;
	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	return (get_texture_color(t, tx, ty));
}

int	sample_floor_color_at(t_game *g, t_ray *r, int y)
{
	double		den;
	double		w;
	double		fx;
	double		fy;

	den = (double)(2 * y - g->mlx.current_height);
	if (den == 0.0)
		den = 1e-6;
	if (r->perp_wall_dist < 1e-6)
		w = 1.0;
	else
		w = ((double)g->mlx.current_height / den) / r->perp_wall_dist;
	floor_wall_point(r, compute_wall_x(g, r), &fx, &fy);
	fx = w * fx + (1.0 - w) * (g->player.pos.x / MAP_SCALE);
	fy = w * fy + (1.0 - w) * (g->player.pos.y / MAP_SCALE);
	return (floor_tex_color(g, fx, fy));
}

void	draw_floor_tex_pixel(t_game *g, t_ray *r, int x, int y)
{
	int			color;

	color = sample_floor_color_at(g, r, y);
	put_pixel(g, x, y, color);
}
