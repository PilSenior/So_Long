/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:53:58 by htekdemi          #+#    #+#             */
/*   Updated: 2025/03/23 23:53:58 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map_elements(t_game *game)
{
	int	i, j, player_count, exit_count;
	
	exit_count = 0;
	player_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'E')
				exit_count++;
			else if (game->map[i][j] == 'P')
				player_count++;
			j++;
		}
		i++;
	}
	if (game->total_collectibles < 1)
		return (ft_printf("Error: Haritada en az bir collectible ('C') olmalı!\n"), 0);
	if (exit_count != 1)
		return (ft_printf("Error: Haritada tam olarak bir çıkış ('E') olmalı!\n"), 0);
	if (player_count != 1)
		return (ft_printf("Error: Haritada tam olarak bir oyuncu ('P') olmalı!\n"), 0);
	return (1);
}

int	check_map_walls(t_game *game)
{
	int	i;

	if ((int)ft_strlen(game->map[0]) != game->map_width || ft_strchr(game->map[0], '0'))
		return (ft_printf("Error: Haritanın üstü duvarlarla kaplı olmalı!\n"), 0);
	if ((int)ft_strlen(game->map[game->map_height - 1]) != game->map_width
		|| ft_strchr(game->map[game->map_height - 1], '0'))
		return (ft_printf("Error: Haritanın altı duvarlarla kaplı olmalı!\n"), 0);
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1'
			|| game->map[i][game->map_width - 1] != '1')
			return (ft_printf("Error: Haritanın yanları duvarlarla kaplı olmalı!\n"), 0);
		i++;
	}
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
			ft_printf("Error: Harita dikdörtgen olmalı!\n");
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
		return(perror("we have a problem"), -1);
	while (get_next_line(fd, &line, &game->saved_line) > 0)
	{
		char *trimmed = ft_strtrim(line, " \t\n\r");
		if (ft_strlen(trimmed) > 0)
			height++;
		free(trimmed);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	close(fd);
	game->map_height = height;
	return (height);
}

char    **read_map(char *filename, t_game *game)
{
    int     fd;
    int     i;
    char    **map;

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
        ft_printf("Error: Harita satir sayisi beklenenle eslesmiyor!\n");
        free_map(map, i);
        return (NULL);
    }
    game->map_width = ft_strlen(map[0]);
    return (map);
}
