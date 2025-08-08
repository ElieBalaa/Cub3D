/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tex_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 10:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_door_texture(t_game *g, t_texture *t)
{
	if (t == &g->door_tex)
		return (1);
	return (0);
}

static int	sample_door_color(t_game *g, t_ray *r, t_texture *t, int tex_y)
{
	int		tex_x;
	double	p;
	int		off;

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

int	compute_tex_y(t_game *g, t_ray *r, t_texture *t, int y)
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

int	sample_wall_color(t_game *g, t_ray *r, t_texture *t, int tex_y)
{
	if (is_door_texture(g, t))
		return (sample_door_color(g, r, t, tex_y));
	return (get_texture_color(t, r->tex_x, tex_y));
}
