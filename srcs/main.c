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

	game->floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &w, &h);
	if (!game->floor)
		error_exit(game, "Floor texture yüklenemedi!");
	
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &w, &h);
	if (!game->wall)
		error_exit(game, "Wall texture yüklenemedi!");
	
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &w, &h);
	if (!game->player)
		error_exit(game, "Player texture yüklenemedi!");
	
	game->collectible = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &w, &h);
	if (!game->collectible)
		error_exit(game, "Collectible texture yüklenemedi!");
	
	game->exit_closed = mlx_xpm_file_to_image(game->mlx, "textures/exit_closed.xpm", &w, &h);
	if (!game->exit_closed)
		error_exit(game, "Exit closed texture yüklenemedi!");
	
	game->exit_open = mlx_xpm_file_to_image(game->mlx, "textures/exit_open.xpm", &w, &h);
	if (!game->exit_open)
		error_exit(game, "Exit open texture yüklenemedi!");
}
int	check_map_characters(t_game *game)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] != '0' && game->map[i][j] != '1' && 
				game->map[i][j] != 'P' && game->map[i][j] != 'C' && 
				game->map[i][j] != 'E')
			{
				ft_printf("Error: Map contains invalid character at position (%d,%d): '%c'\n", 
					i, j, game->map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
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
	if (!check_map_shape(game) || !check_map_walls(game) || !check_map_characters(game))
	{	
		free_game_memory(game);
		exit(1);
	}
	count_collectibles_and_player(game);
	if (!check_map_elements(game))
	{
		free_game_memory(game);
		exit(1);
	}
	if (!check_path_validity(game))
	{
		free_game_memory(game);
		exit(1);
	}
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
	if (file_control(argv[1]) != 1)
	{
		ft_printf("Error: Doesn't exist map file\n");
		return (1);
	}
	game.saved_line = NULL;
	ft_memset(&game, 0, sizeof(t_game));
	game.map = read_map(argv[1], &game);
	if (game.map == NULL)
		return (ft_printf("Maps value is zero\n"), 0);
	init_game(&game);
	draw_map(&game);
	mlx_hook(game.mlx_win, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.mlx_win, 17, 1L << 17, exit_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
