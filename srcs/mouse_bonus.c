/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:20:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/10 12:20:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	apply_rotation_by_delta(t_game *g, double delta)
{
	double		old_dir_x;
	double		old_plane_x;
	double		rot;

	rot = delta * g->player.rot_speed * 0.01;
	old_dir_x = g->player.dir.x;
	g->player.dir.x = g->player.dir.x * cos(rot)
		- g->player.dir.y * sin(rot);
	g->player.dir.y = old_dir_x * sin(rot)
		+ g->player.dir.y * cos(rot);
	old_plane_x = g->player.plane.x;
	g->player.plane.x = g->player.plane.x * cos(rot)
		- g->player.plane.y * sin(rot);
	g->player.plane.y = old_plane_x * sin(rot)
		+ g->player.plane.y * cos(rot);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	static int	initialized = 0;
	int			cx;
	int			cy;
	int			dx;

	(void)y;
	cx = game->mlx.current_width / 2;
	cy = game->mlx.current_height / 2;
	if (!initialized)
	{
		mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, cx, cy);
		initialized = 1;
		return (0);
	}
	dx = x - cx;
	if (dx != 0)
		apply_rotation_by_delta(game, (double)dx);
	mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, cx, cy);
	return (0);
}
