/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:02:21 by htekdemi          #+#    #+#             */
/*   Updated: 2025/04/11 12:02:21 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BUFFER_SIZE 42

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define RESET   "\x1b[0m"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit_closed;
	void	*exit_open;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		total_collectibles;
	int		collected;
	int		move_count;
	char	*saved_line;
	int		exit_count;
	int		player_count;
}	t_game;

int		handle_input(int keycode, t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
void	check_exit(t_game *game, int new_x, int new_y);
void	check_collectible(t_game *game, int new_x, int new_y);
int		exit_game(void *param);

void	init_game(t_game *game);
void	load_textures(t_game *game);
void	draw_map(t_game *game);
void	draw_map_loop(t_game *game, int i, int j);
void	draw_exit(t_game *game, int i, int j);

char	**read_map(char *filename, t_game *game);
int		get_map_size(char *filename, t_game *game);
int		read_lines(int fd, char **map, t_game *game);
int		handle_line(char **map, int i, char *line);
int		allocate_map(char ***map, t_game *game);
void	free_map(char **map, int i);

int		check_map_shape(t_game *game);
int		check_map_walls(t_game *game);
int		validate_map_characters(t_game *game);
void	check_map_elements_count(t_game *game);
int		check_path_validity(t_game *game);

int		open_map_file(char *filename);
int		file_control(char *dst);

void	free_game_memory(t_game *game);
char	*safe_free(char *ptr);

void	error_exit(t_game *game, char *message);

int		get_next_line(int fd, char **line, char **saved_line);

#endif
