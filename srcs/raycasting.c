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

int	calculate_wall_color(double distance)
{
	int	wall_color;

	wall_color = 255 - (int)(distance * 2);
	if (wall_color < 100)
		wall_color = 100;
	wall_color = (wall_color << 16) | (wall_color << 8) | wall_color;
	return (wall_color);
}

void	draw_wall_slice(t_game *game, int x, double distance)
{
	double	height;
	int		start_y;
	int		end_y;
	int		y;
	int		wall_color;

	height = (MAP_SCALE * WINDOW_HEIGHT) / distance;
	start_y = (WINDOW_HEIGHT / 2) - (height / 2);
	end_y = (WINDOW_HEIGHT / 2) + (height / 2);
	if (start_y < 0)
		start_y = 0;
	if (end_y >= WINDOW_HEIGHT)
		end_y = WINDOW_HEIGHT - 1;
	wall_color = calculate_wall_color(distance);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < start_y)
			put_pixel(game, x, y, 0x87CEEB);
		else if (y >= start_y && y <= end_y)
			put_pixel(game, x, y, wall_color);
		else
			put_pixel(game, x, y, 0x8B4513);
		y++;
	}
}

double	cast_single_ray(t_game *game, double angle)
{
	double	ray_x;
	double	ray_y;
	double	cos_angle;
	double	sin_angle;
	int		max_steps;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	ray_x = game->player.pos.x;
	ray_y = game->player.pos.y;
	max_steps = 0;
	while (!touch(ray_x, ray_y, game) && max_steps < 2000)
	{
		ray_x += cos_angle * 0.5;
		ray_y += sin_angle * 0.5;
		max_steps++;
	}
	return (calculate_distance(game->player.pos.x, game->player.pos.y,
			ray_x, ray_y));
}

void	cast_rays_for_3d(t_game *game, double base_angle, double fov_rad)
{
	int		x;
	double	ray_angle;
	double	distance;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = base_angle + (fov_rad / 2.0)
			- (x * fov_rad / WINDOW_WIDTH);
		distance = cast_single_ray(game, ray_angle);
		distance = distance * cos(ray_angle - base_angle);
		draw_wall_slice(game, x, distance);
		x++;
	}
}

void	render_3d_view(t_game *game)
{
	double	base_angle;
	double	fov_rad;

	fov_rad = FOV * M_PI / 180.0;
	base_angle = atan2(game->player.dir.y, game->player.dir.x);
	cast_rays_for_3d(game, base_angle, fov_rad);
}
