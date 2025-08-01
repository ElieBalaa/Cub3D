/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 02:04:38 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 02:23:59 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	contains_cub(char *filename)
{
	char	*type;

	type = ft_strrchr(filename, '.');
	if (!type)
		return (1);
	if (ft_strcmp(type, ".cub") == 0)
		return (0);
	else
		return (1);
}

int	is_valid_char(char c)
{
	return (c != '0' || c != '1' || c != 'N'
		|| c != 'S' || c != 'W' || c != 'E');
}

int	exit_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

int	is_in_minimap_circle(int x, int y, int radius)
{
	int	center_x;
	int	center_y;
	int	dx;
	int	dy;

	center_x = WINDOW_WIDTH - MINIMAP_RADIUS - MINIMAP_MARGIN;
	center_y = WINDOW_HEIGHT - MINIMAP_RADIUS - MINIMAP_MARGIN;
	dx = x - center_x;
	dy = y - center_y;
	return (dx * dx + dy * dy <= radius * radius);
}
