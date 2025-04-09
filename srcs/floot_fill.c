/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:00:00 by htekdemi          #+#    #+#             */
/*   Updated: 2025/04/07 12:00:00 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


static char	**create_map_copy(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static void	free_map_copy(char **map_copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static void	flood_fill_recursive(char **map, int x, int y, t_point size)
{
	if (x < 0 || x >= size.x || y < 0 || y >= size.y)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;

	map[y][x] = 'F';

	flood_fill_recursive(map, x + 1, y, size);
	flood_fill_recursive(map, x - 1, y, size);
	flood_fill_recursive(map, x, y + 1, size);
	flood_fill_recursive(map, x, y - 1, size);
}

int check_path_validity(t_game *game)
{
    char    **map_copy;
    int     x;
    int     y;
    int     valid;
    t_point size;

    map_copy = create_map_copy(game);
    if (!map_copy)
        return (ft_printf("Error: memory split error!\n"), 0);
    size.x = game->map_width;
    size.y = game->map_height;
    flood_fill_recursive(map_copy, game->player_x, game->player_y, size);
    valid = 1;
    y = 0;
    while (y < game->map_height && valid)
    {
        x = 0;
        while (x < game->map_width && valid)
        {
            if (game->map[y][x] == 'C' && map_copy[y][x] != 'F')
                valid = 0;
            if (game->map[y][x] == 'E' && map_copy[y][x] != 'F')
                valid = 0;
            x++;
        }
        y++;
    }
    free_map_copy(map_copy, game->map_height);
    if (!valid)
        ft_printf("Error: Player can't reachable colectibles or exit door!\n");
    return (valid);
}
