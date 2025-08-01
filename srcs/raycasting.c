/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 13:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_line(t_game *game, float start_x)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = game->player.pos.x;
	ray_y = game->player.pos.y;
	while (!touch(ray_x, ray_y, game))
	{
		put_pixel(game, (int)ray_x, (int)ray_y, 0xFF8000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}

void	cast_fov_rays(t_game *game)
{
	int		i;
	int		num_rays;
	double	fov_angle;
	double	ray_angle;
	double	base_angle;

	num_rays = 360;
	fov_angle = 90.0 * M_PI / 180.0;
	base_angle = atan2(game->player.dir.y, game->player.dir.x);
	i = 0;
	while (i < num_rays)
	{
		ray_angle = base_angle + (fov_angle / 2.0)
			* ((double)(i - num_rays / 2) / (double)(num_rays / 2));
		draw_line(game, ray_angle);
		i++;
	}
}

int	ray_hit_wall(t_game *game, double ray_x, double ray_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(ray_x / MAP_SCALE);
	map_y = (int)(ray_y / MAP_SCALE);
	if (map_y >= 0 && map_y < game->map.height
		&& map_x >= 0 && map_x < (int)ft_strlen(game->map.grid[map_y]))
	{
		if (game->map.grid[map_y][map_x] == '1')
			return (1);
		return (0);
	}
	return (1);
}

void	cast_ray(t_game *game, double ray_dir_x, double ray_dir_y)
{
	double	ray_x;
	double	ray_y;
	int		hit;
	t_line	line;

	if (ray_dir_x == 0.0 && ray_dir_y == 0.0)
		return ;
	ray_x = game->player.pos.x;
	ray_y = game->player.pos.y;
	hit = 0;
	while (!hit)
	{
		hit = ray_hit_wall(game, ray_x, ray_y);
		if (!hit)
		{
			ray_x += ray_dir_x * 0.5;
			ray_y += ray_dir_y * 0.5;
		}
	}
	line.start_x = (int)game->player.pos.x;
	line.start_y = (int)game->player.pos.y;
	line.end_x = (int)ray_x;
	line.end_y = (int)ray_y;
	draw_ray_line(game, line);
}

void	draw_direction_line(t_game *game, int player_x, int player_y)
{
	int		i;
	double	line_length;

	line_length = 20.0;
	i = 0;
	while (i <= (int)line_length)
	{
		put_pixel(game,
			player_x + (int)(game->player.dir.x * i),
			player_y + (int)(game->player.dir.y * i),
			COLOR_RED);
		i++;
	}
}
