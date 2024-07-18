# ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <MLX42.h>

typedef struct  s_point
{
    int         x;
    int         y;
}               t_point;

typedef struct  s_plr
{
    int         d;
    int         x;
    int         y;
}               t_plr;

typedef struct  s_data
{
    char        **map;
    t_plr       *plr;
    mlx_t       *mlx;
    mlx_image_t *rays_img;
    mlx_image_t *wall_img;
}               t_data;

void        ft_drop_rays(t_data *data);
char        **ft_split(char const *s, char c);
mlx_keyfunc ft_move_plr(mlx_key_data_t key, t_data *data);

# endif