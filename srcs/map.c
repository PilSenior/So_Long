/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:12:25 by htekdemi          #+#    #+#             */
/*   Updated: 2025/04/11 11:12:25 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int	check_map_walls(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->map_width)
	{
		if (game->map[0][j] != '1'
			|| game->map[game->map_height - 1][j] != '1')
			return (ft_printf(RED "Error: map top or under side's wall "
					"line not correct!\n" RESET), 0);
		j++;
	}
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1'
			|| game->map[i][game->map_width - 1] != '1')
			return (ft_printf(RED "Error: map side walls must be wall!\n"
					RESET), 0);
		i++;
	}
	if (game->map_height < 3 || game->map_width < 3)
		return (ft_printf(RED "Error: Map is too small! Minimum size is 3x3.\n"
				RESET), 0);
	return (1);
}

int	check_map_shape(t_game *game)
{
	int		i;
	size_t	first_width;

	if (!game->map || !game->map[0])
		return (0);
	first_width = ft_strlen(game->map[0]);
	i = 1;
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) != first_width)
		{
			ft_printf(RED "Error: Map must be square!\n" RESET);
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_map_size(char *filename, t_game *game)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf(RED "we have a problem\n" RESET), -1);
	while (get_next_line(fd, &line, &game->saved_line) > 0)
	{
		if (ft_strlen(line) > 0)
			height++;
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	close(fd);
	game->map_height = height;
	return (height);
}

char	**read_map(char *filename, t_game *game)
{
	int		fd;
	int		i;
	char	**map;

	if (get_map_size(filename, game) <= 0)
		return (free_game_memory(game), NULL);
	if (!allocate_map(&map, game))
		return (NULL);
	fd = open_map_file(filename);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	i = read_lines(fd, map, game);
	close(fd);
	if (i != game->map_height)
	{
		ft_printf(RED "Error: Map line count not familiar the expected!\n"
			RESET);
		free_map(map, i);
		return (NULL);
	}
	game->map_width = ft_strlen(map[0]);
	return (map);
}

int	validate_map_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] != '0' && game->map[i][j] != '1'
				&& game->map[i][j] != 'P' && game->map[i][j] != 'C'
				&& game->map[i][j] != 'E')
				return (ft_printf(RED "Error: Map contains invalid character "
						"at position (%d,%d): '%c'\n" RESET,
						i + 1, j + 1, game->map[i][j]), 0);
			j++;
		}
		i++;
	}
	return (1);
}
