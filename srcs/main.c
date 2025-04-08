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
		error_exit(game, "Harita doğrulama hatası!");
	}
	count_collectibles_and_player(game);
	if (!check_map_elements(game))
	{
		error_exit(game, "Harita elemanları hatası!");
	}
	if (!check_path_validity(game))
	{
		error_exit(game, "Geçerli yol bulunamadı!");
	}
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(game, "MLX başlatılamadı!");
		
	game->mlx_win = mlx_new_window(game->mlx, game->map_width * 64,
			game->map_height * 64, "SO_LONG");
	if (!game->mlx_win)
		error_exit(game, "MLX penceresi oluşturulamadı!");
		
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
	{
		ft_printf("Error: Maps value is zero\n");
		return (1);
	}
	
	init_game(&game);
	draw_map(&game);
	
	if (mlx_hook(game.mlx_win, 2, 1L << 0, handle_input, &game) == -1)
		error_exit(&game, "MLX hook hatası!");
		
	if (mlx_hook(game.mlx_win, 17, 1L << 17, exit_game, &game) == -1)
		error_exit(&game, "MLX hook hatası!");
		
	mlx_loop(game.mlx);
	return (0);
}
