/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:30:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 12:30:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_map_lines(char *filename)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	*trim_newline(char *str)
{
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

int	read_map_lines(int fd, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
		{
			game->map.grid[i] = trim_newline(line);
			if (i == 0)
				game->map.width = ft_strlen(game->map.grid[i]);
			i++;
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	game->map.grid[i] = NULL;
	return (0);
}

int	parse_map_file(char *filename, t_game *game)
{
	int	fd;

	game->map.height = count_map_lines(filename);
	if (game->map.height == 0)
		return (1);
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(game->map.grid);
		return (1);
	}
	read_map_lines(fd, game);
	close(fd);
	return (0);
}

void	free_map(t_game *game)
{
	int	i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (game->map.grid[i])
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}
