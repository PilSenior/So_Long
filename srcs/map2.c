/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htekdemi <htekdemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:00:43 by htekdemi          #+#    #+#             */
/*   Updated: 2025/03/24 00:00:43 by htekdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int  open_map_file(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        perror("we can't open the file");
    return (fd);
}

int  allocate_map(char ***map, t_game *game)
{
    *map = malloc(sizeof(char *) * (game->map_height + 1));
    if (!*map)
        return (0);
    return (1);
}

void free_map(char **map, int i)
{
    while (--i >= 0)
        free(map[i]);
    free(map);
}

int  handle_line(char **map, int i, char *line)
{
    char *trimmed = ft_strtrim(line, " \t\n\r");
    if (ft_strlen(trimmed) == 0)
    {
        free(trimmed);
        free(line);
        return (0);
    }
    map[i] = trimmed;
    free(line);
    return (1);
}

int  read_lines(int fd, char **map, t_game *game)
{
    int     i = 0;
    char    *line = NULL;

    if (game->saved_line)
        free(game->saved_line);
    game->saved_line = NULL;
    while (i < game->map_height && get_next_line(fd, &line, &game->saved_line) > 0)
        if (!handle_line(map, i++, line))
            continue;
    map[i] = NULL;
    return (i);
}
