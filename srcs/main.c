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

	if (!game || !game->mlx)
		error_exit(game, "MLX not initialized before loading textures!");
	w = 64;
	h = 64;
	game->floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &w, &h);
	if (!game->floor)
		error_exit(game, "Floor texture loading failed!");
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &w, &h);
	if (!game->wall)
		error_exit(game, "Wall texture loading failed!");
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &w, &h);
	if (!game->player)
		error_exit(game, "Player texture loading failed!");
	game->collectible = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &w, &h);
	if (!game->collectible)
		error_exit(game, "Collectible texture loading failed!");
	game->exit_closed = mlx_xpm_file_to_image(game->mlx, "textures/exit_closed.xpm", &w, &h);
	if (!game->exit_closed)
		error_exit(game, "Exit closed texture loading failed!");
	game->exit_open = mlx_xpm_file_to_image(game->mlx, "textures/exit_open.xpm", &w, &h);
	if (!game->exit_open)
		error_exit(game, "Exit open texture loading failed!");
}
int check_map_characters(t_game *game)
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
	if (!check_map_shape(game) || !check_map_walls(game) || !validate_map_characters(game))
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
	if (!game->mlx)
		error_exit(game, "MLX initialization failed!");
	game->mlx_win = mlx_new_window(game->mlx, game->map_width * 64,
			game->map_height * 64, "SO_LONG");
	if (!game->mlx_win)
		error_exit(game, "Window creation failed!");
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
	if (!file_control(argv[1]))
	{
		ft_printf("Error: Invalid map file extension! Must be '.ber'\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	game.map = read_map(argv[1], &game);
	if (!game.map)
		return (ft_printf("Error: Map loading failed!\n"),1);
	init_game(&game);
	draw_map(&game); 
	mlx_hook(game.mlx_win, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.mlx_win, 17, 0, exit_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
