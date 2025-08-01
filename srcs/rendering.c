/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 12:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	offset = (y * game->mlx.line_length) + (x * (game->mlx.bits_per_pixel / 8));
	dst = game->mlx.img_addr + offset;
	*(unsigned int *)dst = color;
}

void	draw_square(t_game *game, t_square sq)
{
	int	i;
	int	j;

	i = 0;
	while (i < sq.size)
	{
		j = 0;
		while (j < sq.size)
		{
			put_pixel(game, sq.x + j, sq.y + i, sq.color);
			j++;
		}
		i++;
	}
}

void	clear_screen(t_game *game, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	if (!game->map.grid)
		return ;
	y = 0;
	while (y < game->map.height && (y * MAP_SCALE) < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y])
			&& (x * MAP_SCALE) < WINDOW_WIDTH)
		{
			draw_map_cell(game, x, y);
			x++;
		}
		y++;
	}
}
