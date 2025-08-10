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

static int	compute_tex_y_core(int win_h, int line_h, int y, int tex_h)
{
	int	d;
	int	ty;

	d = y * 256 - win_h * 128 + line_h * 128;
	ty = ((d * tex_h) / line_h) / 256;
	return (ty);
}

int	compute_tex_y(t_game *g, t_ray *r, t_texture *t, int y)
{
	int	tex_y;
	int	lh;

	lh = r->line_height;
	if (lh < 1)
		lh = 1;
	tex_y = compute_tex_y_core(g->mlx.current_height, lh, y,
			t->height);
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
