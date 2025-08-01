/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	draw_wall_slice_ceiling(t_game *game, int x, int y)
{
	put_pixel(game, x, y, game->map.ceiling_color);
}

void	draw_wall_slice_wall(t_game *game, t_ray *ray, int x, int y)
{
	int			tex_y;
	int			color;
	double		step;
	double		tex_pos;
	t_texture	*texture;

	texture = get_wall_texture(game, ray);
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (y - ray->draw_start) * step;
	tex_y = (int)tex_pos & (texture->height - 1);
	color = get_texture_color(texture, ray->tex_x, tex_y);
	if (ray->side == 1)
		color = (color >> 1) & 8355711;
	put_pixel(game, x, y, color);
}

void	draw_wall_slice(t_game *game, t_ray *ray, int x, t_texture *texture)
{
	int	y;

	(void)texture;
	y = 0;
	while (y < game->mlx.current_height)
	{
		if (y < ray->draw_start)
			draw_wall_slice_ceiling(game, x, y);
		else if (y >= ray->draw_start && y <= ray->draw_end)
			draw_wall_slice_wall(game, ray, x, y);
		else
			draw_floor_pixel(game, x, y);
		y++;
	}
}
