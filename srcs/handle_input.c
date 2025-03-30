/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   handle_input.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: htekdemi <htekdemi@student.42kocaeli.co	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/23 23:31:40 by htekdemi		  #+#	#+#			 */
/*   Updated: 2025/03/23 23:31:40 by htekdemi		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/so_long.h"

int	exit_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_printf("Oyun kapatiliyor...\n");
	if (game)
		free_game_memory(game);
	exit(0);
	return (0);
}

void	check_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map[new_y][new_x] = '0';
		ft_printf("Collectible toplandi! (%d/%d)\n",
			game->collected, game->total_collectibles);
	}
}

void	check_exit(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E'
		&& game->collected == game->total_collectibles)
	{
		ft_printf("Tebrikler! Oyunu kazandiniz!\n");
		exit_game(game);
	}
}

int	handle_input(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == 65307)
		exit_game(game);
	else if (keycode == 'w' || keycode == 119 || keycode == 65362)
		new_y -= 1;
	else if (keycode == 's' || keycode == 115 || keycode == 65364)
		new_y += 1;
	else if (keycode == 'a' || keycode == 97 || keycode == 65361)
		new_x -= 1;
	else if (keycode == 'd' || keycode == 100 || keycode == 65363)
		new_x += 1;
	else
		return (0);
	move_player(game, new_x, new_y);
	return (0);
}
