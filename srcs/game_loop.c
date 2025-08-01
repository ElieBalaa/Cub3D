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
	if (keycode == KEY_TAB)
		game->view_3d = !game->view_3d;
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

int	game_loop(t_game *game)
{
	int			player_screen_x;
	int			player_screen_y;
	t_square	player_sq;

	process_movement(game);
	process_rotation(game);
	clear_screen(game, COLOR_BLACK);
	if (game->view_3d)
	{
		render_3d_view(game);
	}
	else
	{
		draw_map(game);
		player_screen_x = (int)(game->player.pos.x);
		player_screen_y = (int)(game->player.pos.y);
		player_sq.x = player_screen_x - 8;
		player_sq.y = player_screen_y - 8;
		player_sq.size = 16;
		player_sq.color = 0x00FF00;
		draw_square(game, player_sq);
		draw_direction_line(game, player_screen_x, player_screen_y);
	}
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}
