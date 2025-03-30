#include "../includes/so_long.h"
int file_control(char *dst)
{
    char *src = ".ber";
    int i = 0;
    int k = 0;
    int s = 0;
    while(src[s] != '\0')
        s++;
    while(dst[k] != '\0')
    {
        i = 0;
            while(dst[k] == src[i] && src[i])
            {
                k++;
                i++;
            }
        if(i == s)
            return(1);
        k++;
    }
    return(0);
}

void check_collectible2(t_game *game, int x, int y) {
    if (game->map[y][x] == 'C') {
        game->collected++;
        game->map[y][x] = '0';
        ft_printf("Collectible toplandı! (%d/%d)\n", game->collected, game->total_collectibles);
    }
}


void check_exit2(t_game *game, int x, int y)
{
    if (game->map[y][x] == 'E' && game->collected == game->total_collectibles)
    {
        ft_printf("Tebrikler! Oyunu kazandınız!\n");
        free_game_memory(game);  // Use our complete cleanup function
        exit(0);
    }
}


void move_player(t_game *game, int new_x, int new_y) {
    // Koordinatların harita sınırları içinde olup olmadığını kontrol edelim
    if (new_x < 0 || new_x >= game->map_width || new_y < 0 || new_y >= game->map_height) {
        return;  // Hata önlendi, fonksiyon burada bitiyor
    }

    if (game->map[new_y][new_x] != '1') 
    {
        int old_x = game->player_x;
        int old_y = game->player_y;
        
        check_collectible2(game, new_x, new_y);
        check_exit2(game, new_x, new_y);
        
        if (game->map[new_y][new_x] != 'E') {
            if (game->player_x != new_x || game->player_y != new_y)
                game->move_count++;
                
            if (game->map[old_y][old_x] == 'P')
                game->map[old_y][old_x] = '0';
                
            game->player_x = new_x;
            game->player_y = new_y;
            
            if (game->map[new_y][new_x] != 'E')
                game->map[new_y][new_x] = 'P';
        }
        ft_printf("Hareket Sayısı: %d\n", game->move_count);
    }
    draw_map(game);
}
