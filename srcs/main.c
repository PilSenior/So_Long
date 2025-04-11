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
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"

void	load_textures(t_game *game)
{
	int	w;
	int	h;

	if (!game || !game->mlx)
		error_exit(game, "MLX not initialized before loading textures!");
	w = 1;
	h = 1;
	game->floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &w, &h);
	game->wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &w, &h);
	game->player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &w, &h);
	game->collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &w, &h);
	game->exit_closed = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_closed.xpm", &w, &h);
	game->exit_open = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_open.xpm", &w, &h);
	if (!game->exit_open || !game->exit_closed || !game->collectible
		|| !game->player || !game->wall || !game->floor)
		error_exit(game, "Exit open texture loading failed!");
}

void	count_collectibles_and_player(t_game *game)
{
	int	i;
	int	j;

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
				game->player_count++;
			}
			else if (game->map[i][j] == 'C')
				game->total_collectibles++;
			else if (game->map[i][j] == 'E')
				game->exit_count++;
			j++;
		}
		i++;
	}
	check_map_elements_count(game);
}

void	init_game(t_game *game)
{
	if (!check_map_shape(game) || !check_map_walls(game)
		|| !validate_map_characters(game))
	{
		free_game_memory(game);
		exit(1);
	}
	game->total_collectibles = 0;
	game->collected = 0;
	game->exit_closed = 0;
	count_collectibles_and_player(game);
	if (!check_path_validity(game))
	{
		free_game_memory(game);
		exit(1);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_printf(RED "MLX initialization failed!" RESET);
	game->mlx_win = mlx_new_window(game->mlx, game->map_width * 64,
			game->map_height * 64, "SO_LONG");
	if (!game->mlx_win)
		ft_printf(RED "Window creation failed!" RESET);
	load_textures(game);
	game->move_count = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf(RED "Error: Missing map file!\n" RESET);
		return (1);
	}
	if (!file_control(argv[1]))
	{
		ft_printf(RED "Error: Invalid map file extension! Must be '.ber'\n"
			RESET);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	game.map = read_map(argv[1], &game);
	if (!game.map)
		return (ft_printf("Error: Map loading failed!\n"), 1);
	init_game(&game);
	draw_map(&game);
	mlx_hook(game.mlx_win, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.mlx_win, 17, 0, exit_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
