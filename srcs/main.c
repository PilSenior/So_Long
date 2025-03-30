/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:49:13 by htekdemi          #+#    #+#             */
/*   Updated: 2025/03/23 23:49:13 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_textures(t_game *game)
{
	int	w;
	int	h;

	game->floor = mlx_xpm_file_to_image
		(game->mlx, "textures/floor.xpm", &w, &h);
	game->wall = mlx_xpm_file_to_image
		(game->mlx, "textures/wall.xpm", &w, &h);
	game->player = mlx_xpm_file_to_image
		(game->mlx, "textures/player.xpm", &w, &h);
	game->collectible = mlx_xpm_file_to_image
		(game->mlx, "textures/collectible.xpm", &w, &h);
	game->exit_closed = mlx_xpm_file_to_image
		(game->mlx, "textures/exit_closed.xpm", &w, &h);
	game->exit_open = mlx_xpm_file_to_image
		(game->mlx, "textures/exit_open.xpm", &w, &h);
}

void	count_collectibles_and_player(t_game *game)
{
	int	i;
	int	j;

	game->total_collectibles = 0;
	game->collected = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
			}
			else if (game->map[i][j] == 'C')
				game->total_collectibles++;
			j++;
		}
		i++;
	}
}

void	init_game(t_game *game)
{
	if (!check_map_shape(game) || !check_map_walls(game))
		exit(1);
	count_collectibles_and_player(game);
	if (!check_map_elements(game))
		exit(1);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->map_width * 64,
			game->map_height * 64, "SO_LONG");
	load_textures(game);
	game->move_count = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error: Missing map file!\n");
		return (1);
	}
	if(file_control(argv[1]) != 1)
	{
		ft_printf("Error: Doesn't exist map file\n");
		return(1);
	}
	game.saved_line = NULL;
	ft_memset(&game, 0, sizeof(t_game));
	game.map = read_map(argv[1], &game);
	if(game.map == NULL)
		return(ft_printf("Maps value is zero"), 0);	
	init_game(&game);
	draw_map(&game);
	mlx_hook(game.mlx_win, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.mlx_win, 17, 1L << 17, exit_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
