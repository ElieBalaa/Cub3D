/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
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

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	if (!path)
		return (1);
	texture->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (0);
}

int	load_textures(t_game *game)
{
	if (!game->map.north_texture || !game->map.south_texture
		|| !game->map.west_texture || !game->map.east_texture)
		return (1);
	if (load_texture(game, &game->textures[0], game->map.north_texture))
		return (1);
	if (load_texture(game, &game->textures[1], game->map.south_texture))
		return (1);
	if (load_texture(game, &game->textures[2], game->map.west_texture))
		return (1);
	if (load_texture(game, &game->textures[3], game->map.east_texture))
		return (1);
	if (load_texture(game, &game->door_tex, "./textures/door/door.xpm"))
		return (1);
	if (load_texture(game, &game->floor_tex, "./textures/floor/floor.xpm"))
		return (1);
	return (0);
}
