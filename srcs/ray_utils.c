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

int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

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

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map.x - game->player.pos.x / MAP_SCALE
				+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map.y - game->player.pos.y / MAP_SCALE
				+ (1 - ray->step.y) / 2) / ray->dir.y;
	ray->line_height = (int)(game->mlx.current_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->mlx.current_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->mlx.current_height / 2;
	if (ray->draw_end >= game->mlx.current_height)
		ray->draw_end = game->mlx.current_height - 1;
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
