/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:30:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 11:30:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (exit_error("Error: Failed to initialize MLX"));
	game->mlx.current_width = WINDOW_WIDTH;
	game->mlx.current_height = WINDOW_HEIGHT;
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr,
		game->mlx.current_width, game->mlx.current_height, "Cub3D");
	if (!game->mlx.win_ptr)
		return (exit_error("Error: Failed to create window"));
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr,
		game->mlx.current_width, game->mlx.current_height);
	if (!game->mlx.img_ptr)
		return (exit_error("Error: Failed to create image"));
	game->mlx.img_addr = mlx_get_data_addr(game->mlx.img_ptr,
			&game->mlx.bits_per_pixel, &game->mlx.line_length,
			&game->mlx.endian);
	return (0);
}

int	init_player(t_game *game)
{
	game->player.pos.x = 25 * MAP_SCALE + MAP_SCALE / 2;
	game->player.pos.y = 11 * MAP_SCALE + MAP_SCALE / 2;
	game->player.dir.x = 0.0;
	game->player.dir.y = -1.0;
	game->player.plane.x = 0.66;
	game->player.plane.y = 0.0;
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
	return (0);
}

int	init_map(t_game *game)
{
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
	game->map.floor_color = COLOR_BLACK;
	game->map.ceiling_color = COLOR_WHITE;
	return (0);
}

int	init_game(t_game *game)
{
	if (init_mlx(game) || init_player(game) || init_map(game))
		return (1);
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.shift = 0;
	game->fullscreen = 0;
	return (0);
}

void	cleanup_game(t_game *game)
{
	free_map(game);
	if (game->mlx.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.mlx_ptr)
		mlx_destroy_display(game->mlx.mlx_ptr);
	if (game->mlx.mlx_ptr)
		free(game->mlx.mlx_ptr);
}
