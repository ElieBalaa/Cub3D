/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:08:59 by oiskanda          #+#    #+#             */
/*   Updated: 2025/08/01 00:43:09 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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

int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%d\n", contains_cub(argv[1]));
}
