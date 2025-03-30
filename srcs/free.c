/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: htekdemi <htekdemi@student.42kocaeli.co	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/23 23:13:26 by htekdemi		  #+#	#+#			 */
/*   Updated: 2025/03/23 23:13:26 by htekdemi		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*safe_free(char *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
void	free_map_memory(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			if (game->map[i])
			{
				free(game->map[i]);
				game->map[i] = NULL;
			}
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void	free_textures(t_game *game)
{
	if (game->mlx)
	{
		if (game->wall)
			mlx_destroy_image(game->mlx, game->wall);
		if (game->floor)
			mlx_destroy_image(game->mlx, game->floor);
		if (game->player)
			mlx_destroy_image(game->mlx, game->player);
		if (game->collectible)
			mlx_destroy_image(game->mlx, game->collectible);
		if (game->exit_closed)
			mlx_destroy_image(game->mlx, game->exit_closed);
		if (game->exit_open)
			mlx_destroy_image(game->mlx, game->exit_open);
	}
}

void	free_mlx(t_game *game)
{
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_game_memory(t_game *game)
{
	free_map_memory(game);
	if (game->saved_line)
	{
		free(game->saved_line);
		game->saved_line = NULL;
	}
	free_textures(game);
	free_mlx(game);
}
