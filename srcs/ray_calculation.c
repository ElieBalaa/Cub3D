/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map.x - game->player.pos.x / MAP_SCALE
				+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map.y - game->player.pos.y / MAP_SCALE
				+ (1 - ray->step.y) / 2) / ray->dir.y;
}

void	calculate_perp_wall_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map.x - game->player.pos.x / MAP_SCALE
				+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map.y - game->player.pos.y / MAP_SCALE
				+ (1 - ray->step.y) / 2) / ray->dir.y;
}

void	calculate_line_height_and_draw_range(t_game *game, t_ray *ray)
{
	ray->line_height = (int)(game->mlx.current_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->mlx.current_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->mlx.current_height / 2;
	if (ray->draw_end >= game->mlx.current_height)
		ray->draw_end = game->mlx.current_height - 1;
}

void	calculate_floor_coords(t_game *game, int x, int y, double *floor_x)
{
	double	row_distance;
	double	camera_x;
	double	floor_y;

	camera_x = 2 * x / (double)game->mlx.current_width - 1;
	row_distance = (double)game->mlx.current_height / (2.0 * y
			- game->mlx.current_height);
	*floor_x = game->player.pos.x / MAP_SCALE + row_distance
		* (game->player.dir.x + game->player.plane.x * camera_x);
	floor_y = game->player.pos.y / MAP_SCALE + row_distance
		* (game->player.dir.y + game->player.plane.y * camera_x);
	*(floor_x + 1) = floor_y;
}

void	calculate_wall_texture_coords(t_game *game,
			t_ray *ray, t_texture *texture)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos.y / MAP_SCALE + ray->perp_wall_dist
			* ray->dir.y;
	else
		wall_x = game->player.pos.x / MAP_SCALE + ray->perp_wall_dist
			* ray->dir.x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->dir.x > 0) || (ray->side == 1
			&& ray->dir.y < 0))
		ray->tex_x = texture->width - ray->tex_x - 1;
}
