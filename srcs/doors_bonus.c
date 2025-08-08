/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 10:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_inside(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return (0);
	return (1);
}

static int	front_cell(t_game *game, int *mx, int *my)
{
	double	fx;
	double	fy;

	fx = game->player.pos.x / MAP_SCALE + game->player.dir.x;
	fy = game->player.pos.y / MAP_SCALE + game->player.dir.y;
	*mx = (int)fx;
	*my = (int)fy;
	return (is_inside(game, *mx, *my));
}

void	try_toggle_door(t_game *game)
{
	int	mx;
	int	my;

	if (!front_cell(game, &mx, &my))
		return ;
	if (game->map.grid[my][mx] == 'D')
		set_door_target(game, mx, my, 1);
	else if (game->map.grid[my][mx] == 'O')
		set_door_target(game, mx, my, 0);
}
