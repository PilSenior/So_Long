/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:26:17 by htekdemi          #+#    #+#             */
/*   Updated: 2025/03/31 12:26:17 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	file_control(char *dst)
{
	int	len;

	len = ft_strlen(dst);
	// Dosya adı en az 4 karakter olmalı (.ber)
	if (len < 5)
		return (0);
	// Son 4 karakterin .ber olup olmadığını kontrol et
	if (dst[len - 4] == '.' && dst[len - 3] == 'b' && 
		dst[len - 2] == 'e' && dst[len - 1] == 'r')
		return (1);
	return (0);
}

void	check_collectible(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
	{
		game->collected++;
		game->map[y][x] = '0';
		ft_printf("Collectible toplandı! (%d/%d)\n",
			game->collected, game->total_collectibles);
	}
	ft_printf("Move Count: %d\n", game->move_count);
}

void	check_exit(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E' && game->collected == game->total_collectibles)
	{
		ft_printf("We have a winner!\n");
		free_game_memory(game);
		exit(0);
	}
}

void	move_player(t_game *game, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	if (new_x < 0 || new_x >= game->map_width || new_y < 0
		|| new_y >= game->map_height)
		return ;
	if (game->map[new_y][new_x] != '1')
	{
		old_x = game->player_x;
		old_y = game->player_y;
		check_collectible(game, new_x, new_y);
		check_exit(game, new_x, new_y);
		if (game->map[new_y][new_x] != '1')
		{
			if (game->player_x != new_x || game->player_y != new_y)
				game->move_count++;
			if (game->map[old_y][old_x] == 'P')
				game->map[old_y][old_x] = '0';
			game->player_x = new_x;
			game->player_y = new_y;
			if (game->map[new_y][new_x] != 'E')
				game->map[new_y][new_x] = 'P';
		}
	}
	draw_map(game);
}
