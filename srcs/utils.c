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
