/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 12:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_floor_pixel(t_game *game, int x, int y)
{
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;
	int		color;

	calculate_floor_coords(game, x, y, &floor_x);
	floor_y = *(double *)(&floor_x + 1);
	tex_x = (int)(floor_x * game->floor_texture.width)
		% game->floor_texture.width;
	tex_y = (int)(floor_y * game->floor_texture.height)
		% game->floor_texture.height;
	if (tex_x < 0)
		tex_x += game->floor_texture.width;
	if (tex_y < 0)
		tex_y += game->floor_texture.height;
	color = get_texture_color(&game->floor_texture, tex_x, tex_y);
	put_pixel(game, x, y, color);
}

void	draw_textured_wall(t_game *game, t_ray *ray, int x)
{
	t_texture	*texture;

	texture = get_wall_texture(game, ray);
	calculate_wall_texture_coords(game, ray, texture);
	draw_wall_slice(game, ray, x, texture);
}

void	cast_ray(t_game *game, int x)
{
	t_ray	ray;

	init_ray(game, &ray, x);
	calculate_step_and_side_dist(game, &ray);
	perform_dda(game, &ray);
	calculate_perp_wall_dist(game, &ray);
	calculate_line_height_and_draw_range(game, &ray);
	draw_textured_wall(game, &ray, x);
}

void	render_3d_view(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->mlx.current_width)
	{
		cast_ray(game, x);
		x++;
	}
}
