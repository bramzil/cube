# ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "MLX42/MLX42.h"
# include <stdarg.h>

typedef struct  s_point
{
    double         x;
    double         y;
}               t_point;


typedef struct  s_plr
{
    double          d;
    double          x;
    double          y;
}               t_plr;

typedef struct  s_texture
{
    int             wd;
    int             ht;
    int32_t         *tb;
}               t_texture;

typedef struct  s_face
{
    char            typ;
    char            dir;
    char            fix;
    int             rays;
    double          x_ref;
    double          y_ref;
    double          height_1;
    double          height_2;
    struct s_face   *next;
}                t_face;

typedef struct  s_data
{
    char            **map;
    int             wnd_ht;
    int             wnd_wd;
    int             grd_ht;
    int             grd_wd;
    t_plr           plr;
    double          fact;
    mlx_t           *mlx;
    t_point         *array;
    t_texture       w_text;
    t_texture       d_text;
    t_face          *face_lst;
    mlx_image_t     *rays_img;
    mlx_image_t     *map_img;
    mlx_image_t     *ddd__img;
}               t_data;

void        ft_move_plr(mlx_key_data_t key, void *arg);
t_face      *new_node(double x_ref, double y_ref);
int         ft_free_lst(t_face *lst);
int         ft_mini_map(t_data *data);
void        ft_cast_rays(t_data *data);
char        **ft_split(char const *s, char c);
double      get_height(t_data *data, int i);
t_face      *ft_create_list(t_data *data);
void        ft_render_wall(t_data *data);
double      real_angle(double angle);
int         ft_check_next(t_data *data, double x, double y);
double      ft_get_inter(t_data *data, t_point *inter, double angle);

# endif