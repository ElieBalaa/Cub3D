/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (ray->map.x < 0 || ray->map.y < 0 || ray->map.x >= game->map.width
			|| ray->map.y >= game->map.height
			|| game->map.grid[(int)ray->map.y][(int)ray->map.x] == '1')
			ray->hit = 1;
	}
}

void	calculate_perp_wall_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (fabs(ray->dir.x) < 1e-10)
			ray->perp_wall_dist = 1e30;
		else
			ray->perp_wall_dist = (ray->map.x - game->player.pos.x / MAP_SCALE
					+ (1 - ray->step.x) / 2) / ray->dir.x;
	}
	else
	{
		if (fabs(ray->dir.y) < 1e-10)
			ray->perp_wall_dist = 1e30;
		else
			ray->perp_wall_dist = (ray->map.y - game->player.pos.y / MAP_SCALE
					+ (1 - ray->step.y) / 2) / ray->dir.y;
	}
}

void	calculate_line_height_and_draw_range(t_game *game, t_ray *ray)
{
	ray->line_height = (int)(game->mlx.current_height / ray->perp_wall_dist);
	if (ray->line_height > game->mlx.current_height * 3)
		ray->line_height = game->mlx.current_height * 3;
	ray->draw_start = -ray->line_height / 2 + game->mlx.current_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->mlx.current_height / 2;
	if (ray->draw_end >= game->mlx.current_height)
		ray->draw_end = game->mlx.current_height - 1;
}

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	calculate_perp_wall_dist(game, ray);
	calculate_line_height_and_draw_range(game, ray);
}

t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (&game->textures[3]);
		else
			return (&game->textures[2]);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->textures[1]);
		else
			return (&game->textures[0]);
	}
}
