# ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "../ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
#include <string.h>
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
	time_t	start_time;
	char    *saved_line;
}	t_game;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

int		handle_input(int keycode, t_game *game);
char	**read_map(char *filename, t_game *game);
int		validate_map(char **map);
void	draw_map(t_game *game);
void	check_xpm_files(t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
int		exit_game(void *param);
void	check_exit(t_game *game, int new_x, int new_y);
void	check_collectible(t_game *game, int new_x, int new_y);
void	draw_tile(t_game *game, int i, int j);
void	draw_exit(t_game *game, int i, int j);
void	init_game(t_game *game);
void	count_collectibles_and_player(t_game *game);
void	load_textures(t_game *game);
void	render_map(t_game *game);
int 	get_map_size(char *filename, t_game *game);
int		check_map_shape(t_game *game);
int		check_map_walls(t_game *game);
int		check_map_elements(t_game *game);
void	free_game_memory(t_game *game);
void 	free_game_memory2(t_game *game);
int 	get_next_line(int fd, char **line, char **saved_line);
void	draw_map_loop(t_game *game, int i, int j);
char	*safe_free(char *ptr);
int  	read_lines(int fd, char **map, t_game *game);
int  	handle_line(char **map, int i, char *line);
void 	free_map(char **map, int i);
int  	allocate_map(char ***map, t_game *game);
int  	open_map_file(char *filename);
int 	file_control(char *dst);
int		count_map_characters(t_game *game, int *exit_count, int *player_count);
int 	check_path_validity(t_game *game);
void	error_exit(t_game *game, char *message);
int		validate_map_characters(t_game *game);
#endif