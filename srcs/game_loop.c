/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:35:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 11:35:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	if (keycode == KEY_SHIFT)
		game->keys.shift = 1;
	if (keycode == KEY_F)
		toggle_fullscreen(game);
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	if (keycode == KEY_A)
		game->keys.a = 0;
	if (keycode == KEY_S)
		game->keys.s = 0;
	if (keycode == KEY_D)
		game->keys.d = 0;
	if (keycode == KEY_LEFT)
		game->keys.left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	if (keycode == KEY_SHIFT)
		game->keys.shift = 0;
	return (0);
}

void	toggle_fullscreen(t_game *game)
{
	int	new_width;
	int	new_height;

	if (game->fullscreen)
	{
		new_width = WINDOW_WIDTH;
		new_height = WINDOW_HEIGHT;
	}
	else
	{
		new_width = FULLSCREEN_WIDTH;
		new_height = FULLSCREEN_HEIGHT;
	}
	if (game->mlx.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	game->mlx.current_width = new_width;
	game->mlx.current_height = new_height;
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr,
		new_width, new_height, "Cub3D");
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr,
		new_width, new_height);
	game->mlx.img_addr = mlx_get_data_addr(game->mlx.img_ptr,
		&game->mlx.bits_per_pixel, &game->mlx.line_length,
		&game->mlx.endian);
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->mlx.win_ptr, 17, 1L << 17, close_game, game);
	game->fullscreen = !game->fullscreen;
}

int	game_loop(t_game *game)
{
	process_movement(game);
	process_rotation(game);
	clear_screen(game, COLOR_BLACK);
	render_3d_view(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}
