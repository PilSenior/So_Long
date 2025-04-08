/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:26:20 by htekdemi          #+#    #+#             */
/*   Updated: 2025/03/31 12:26:20 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	count_map_characters(t_game *game, int *exit_count, int *player_count)
{
	int	i;
	int	j;

	*exit_count = 0;
	*player_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'E')
				(*exit_count)++;
			else if (game->map[i][j] == 'P')
				(*player_count)++;
			j++;
		}
		i++;
	}
	return (1);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->wall, x * 64, y * 64);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->floor, x * 64, y * 64);
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->player, x * 64, y * 64);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->collectible, x * 64, y * 64);
			x++;
		}
		y++;
	}
}
