/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_stubs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_map_cell(t_game *game, int x, int y)
{
	(void)game;
	(void)x;
	(void)y;
}

int	check_collision(t_game *game, double x, double y)
{
	(void)game;
	(void)x;
	(void)y;
	return (0);
}

void	draw_floor_tex_pixel(t_game *game, t_ray *ray, int x, int y)
{
	(void)ray;
	put_pixel(game, x, y, game->map.floor_color);
}

int	sample_floor_color_at(t_game *game, t_ray *ray, int y)
{
	(void)ray;
	(void)y;
	return (game->map.floor_color);
}
