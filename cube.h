# ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "MLX42/MLX42.h"

typedef struct      s_point
{
    double          x;
    double          y;
}                   t_point;

typedef struct  s_face
{
    int             i;
    int             j;
    int             rays;
    double          height_1;
    double          height_2;
    double          step;
    struct s_face   *next;
}                   t_face;

typedef struct      s_line
{
    double          x;
    double          y;
    double          inc_x;
    double          inc_y;   
}                   t_line;

typedef struct  s_plr
{
    int             d;
    double          x;
    double          y;
}                   t_plr;

typedef struct  s_data
{
    char            **map;
    t_plr           *plr;
    mlx_t           *mlx;
    t_point         *array;
    t_face          *face_lst;
    mlx_image_t     *rays_img;
    mlx_image_t     *wall_img;
    mlx_image_t     *img_3d;
}               t_data;

void        ft_drop_rays(t_data *data);
char        **ft_split(char const *s, char c);
mlx_keyfunc ft_move_plr(mlx_key_data_t key, t_data *data);
int         ft_render_line(t_data *data, double dst, double x);

# endif