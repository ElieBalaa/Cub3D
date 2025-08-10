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
	if (keycode == KEY_E)
		try_toggle_door(game);
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
	destroy_window_and_image(game);
	create_new_window_and_image(game, new_width, new_height);
	register_event_handlers(game);
	game->fullscreen = !game->fullscreen;
}

int	game_loop(t_game *game)
{
	process_movement(game);
	process_rotation(game);
	update_doors(game);
	clear_screen(game, COLOR_BLACK);
	render_3d_view(game);
	draw_minimap(game);
	draw_weapon_hud(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}
