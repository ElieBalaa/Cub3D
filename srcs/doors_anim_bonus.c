/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_anim_bonus.c                                  :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 10:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

static double	now_seconds(void)
{
	struct timeval	v;

	gettimeofday(&v, NULL);
	return ((double)v.tv_sec + (double)v.tv_usec / 1e6);
}

int	init_doors_anim(t_game *game)
{
	int	y;
	int	x;

	game->door_prog = (double **)malloc(sizeof(double *) * game->map.height);
	game->door_target = (char **)malloc(sizeof(char *) * game->map.height);
	y = 0;
	while (game->map.grid[y])
	{
		game->door_prog[y] = (double *)malloc(sizeof(double)
			* ft_strlen(game->map.grid[y]));
		game->door_target[y] = (char *)malloc(sizeof(char)
			* ft_strlen(game->map.grid[y]));
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			game->door_prog[y][x] = (game->map.grid[y][x] == 'O');
			game->door_target[y][x] = (game->map.grid[y][x] == 'O');
			x++;
		}
		y++;
	}
	game->door_last_ts = now_seconds();
	return (0);
}

void	set_door_target(t_game *game, int x, int y, int opening)
{
	if (y < 0 || y >= game->map.height)
		return ;
	if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return ;
	if (game->map.grid[y][x] != 'D' && game->map.grid[y][x] != 'O')
		return ;
	game->door_target[y][x] = (opening != 0);
}

static void	update_row(t_game *g, int y, double speed, double dt)
{
	int		x;
	double	p;
	int		t;
	char	c;

	x = 0;
	while (x < (int)ft_strlen(g->map.grid[y]))
	{
		c = g->map.grid[y][x];
		if (c != 'D' && c != 'O')
		{
			x++;
			continue ;
		}
		p = g->door_prog[y][x];
		t = g->door_target[y][x];
		if (t && p < 1.0)
			p += speed * dt;
		else if (!t && p > 0.0)
			p -= speed * dt;
		if (p > 1.0)
			p = 1.0;
		if (p < 0.0)
			p = 0.0;
		g->door_prog[y][x] = p;
		if (p >= 1.0)
			g->map.grid[y][x] = 'O';
		else if (p <= 0.0)
			g->map.grid[y][x] = 'D';
		x++;
	}
}

void	update_doors(t_game *game)
{
	double	now;
	double	dt;
	double	speed;
	int		y;

	now = now_seconds();
	dt = now - game->door_last_ts;
	game->door_last_ts = now;
	speed = 2.0;
	y = 0;
	while (game->map.grid[y])
	{
		update_row(game, y, speed, dt);
		y++;
	}
}
