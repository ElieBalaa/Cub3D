/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/12 12:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_health(t_game *g)
{
	g->max_health = 100;
	g->health = 100;
	g->last_hit_ts = -10.0;
	g->invuln_secs = 0.6;
	g->is_dead = 0;
}

static int	is_invulnerable(t_game *g)
{
	double	dt;

	dt = now_seconds() - g->last_hit_ts;
	if (dt < g->invuln_secs)
		return (1);
	return (0);
}

void	apply_damage(t_game *g, int amount)
{
	if (amount <= 0 || g->is_dead)
		return ;
	if (is_invulnerable(g))
		return ;
	g->health -= amount;
	if (g->health < 0)
		g->health = 0;
	g->last_hit_ts = now_seconds();
	if (g->health == 0)
		g->is_dead = 1;
}

void	heal_player(t_game *g, int amount)
{
	if (amount <= 0)
		return ;
	g->health += amount;
	if (g->health > g->max_health)
		g->health = g->max_health;
}

static void	draw_texture_scaled(t_game *g, t_texture *t,
			int dx, int dy, int tw, int th)
{
	int	x;
	int	y;
	int	sx;
	int	sy;
	int	c;
	int	key;

	if (!t->img || tw <= 0 || th <= 0)
		return ;
	key = get_texture_color(t, 0, 0);
	y = 0;
	while (y < th)
	{
		sy = (y * t->height) / th;
		x = 0;
		while (x < tw)
		{
			sx = (x * t->width) / tw;
			c = get_texture_color(t, sx, sy);
			if (c != key)
				put_pixel(g, dx + x, dy + y, c);
			x++;
		}
		y++;
	}
}

static void	draw_bar_fill_scaled(t_game *g, int x, int y,
			int fw, int fh)
{
	int	xi;
	int	yi;
	int	sx;
	int	sy;
	int	c;
	int	key;

	if (!g->hp_bar_fill.img || fw <= 0 || fh <= 0)
		return ;
	key = get_texture_color(&g->hp_bar_fill, 0, 0);
	yi = 0;
	while (yi < fh)
	{
		sy = (yi * g->hp_bar_fill.height) / fh;
		xi = 0;
		while (xi < fw)
		{
			sx = (xi * g->hp_bar_fill.width) / fw;
			c = get_texture_color(&g->hp_bar_fill, sx, sy);
			if (c != key)
				put_pixel(g, x + xi, y + yi, c);
			xi++;
		}
		yi++;
	}
}

void	draw_health_hud(t_game *g)
{
	int	margin;
	int	bg_w;
	int	bg_h;
	int	bar_x;
	int	bar_y;
	int	fill_w;
	int	icon_w;
	int	icon_h;
	int	icon_x;
	int	icon_y;

	margin = 2;
	bg_w = g->hp_bar_bg.width / 2;
	bg_h = g->hp_bar_bg.height / 2;
	icon_w = g->hp_icon.width / 10;
	if (icon_w < 1)
		icon_w = 1;
	icon_h = g->hp_icon.height / 10;
	if (icon_h < 1)
		icon_h = 1;
	icon_x = margin;
	bar_x = icon_x + icon_w + 4;
	bar_y = g->mlx.current_height - bg_h - margin;
	icon_y = bar_y + (bg_h - icon_h) / 2;
	draw_texture_scaled(g, &g->hp_bar_bg, bar_x, bar_y, bg_w, bg_h);
	fill_w = 0;
	if (g->max_health > 0)
		fill_w = (g->health * bg_w) / g->max_health;
	draw_bar_fill_scaled(g, bar_x, bar_y, fill_w, bg_h);
	draw_texture_scaled(g, &g->hp_icon, icon_x, icon_y, icon_w, icon_h);
}

void	handle_death_and_respawn(t_game *g)
{
	if (!g->is_dead)
		return ;
} 