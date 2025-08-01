/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	destroy_window_and_image(t_game *game)
{
	if (game->mlx.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
}

void	create_new_window_and_image(t_game *game, int new_width, int new_height)
{
	game->mlx.current_width = new_width;
	game->mlx.current_height = new_height;
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr,
			new_width, new_height, "Cub3D");
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr,
			new_width, new_height);
	game->mlx.img_addr = mlx_get_data_addr(game->mlx.img_ptr,
			&game->mlx.bits_per_pixel,
			&game->mlx.line_length, &game->mlx.endian);
}

void	register_event_handlers(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->mlx.win_ptr, 17, 1L << 17, close_game, game);
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->mlx.current_width - 1;
	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	ray->map.x = (int)game->player.pos.x / MAP_SCALE;
	ray->map.y = (int)game->player.pos.y / MAP_SCALE;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
}

void	calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x / MAP_SCALE - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->player.pos.x
				/ MAP_SCALE) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y / MAP_SCALE - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - game->player.pos.y
				/ MAP_SCALE) * ray->delta_dist.y;
	}
}
