/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:56:00 by htekdemi          #+#    #+#             */
/*   Updated: 2025/03/23 21:56:00 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../minilibx/mlx.h"
#include <stdlib.h>

void	error_exit(t_game *game, char *message)
{
	if (message)
		ft_printf("Error: %s\n", message);
	free_game_memory(game);
	exit(1);
}

void	draw_exit(t_game *game, int i, int j)
{
	if (game->map[i][j] == 'E')
	{
		if (game->collected == game->total_collectibles)
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win,
				game->exit_open, j * 64, i * 64);
		}
		else
			mlx_put_image_to_window(game->mlx, game->mlx_win,
				game->exit_closed, j * 64, i * 64);
	}
}

void	draw_map_loop(t_game *game, int i, int j)
{
	while (j < game->map_width)
	{
		if (game->map[i][j] == '1')
			mlx_put_image_to_window(game->mlx, game->mlx_win,
				game->wall, j * 64, i * 64);
		else if (game->map[i][j] == '0')
			mlx_put_image_to_window(game->mlx, game->mlx_win,
				game->floor, j * 64, i * 64);
		else if (game->map[i][j] == 'C')
			mlx_put_image_to_window(game->mlx, game->mlx_win,
				game->collectible, j * 64, i * 64);
		else if (game->map[i][j] == 'E')
			draw_exit(game, i, j);
		j++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		draw_map_loop(game, i, j);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->player,
		game->player_x * 64, game->player_y * 64);
}
