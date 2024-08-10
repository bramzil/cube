# ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <MLX42.h>
# include <stdarg.h>

typedef struct  s_point
{
    double         x;
    double         y;
}               t_point;

typedef struct  s_door
{
    int             i;
    int             j;
    int             var;
    char            state;
}               t_door;

typedef struct  s_plr
{
    double          d;
    double          h;
    double          x;
    double          y;
}               t_plr;

typedef struct  s_face
{
    char            dir;
    char            fix;
    int             rays;
    double          height;
    struct s_face   *next;
}                t_face;

typedef struct  s_gun
{
    int             i;
    char            sht;
    int             nbr_sht;
    mlx_image_t     *arr[13];
}               t_gun;

typedef struct  s_data
{
    char            **map;
    int             wnd_ht;
    int             wnd_wd;
    int             grd_ht;
    int             grd_wd;
    int             doors_nbr;
    double          fact;
    t_plr           plr;
    t_gun           gun;
    mlx_t           *mlx;
    int32_t         *N_texture;
    int32_t         *S_texture;
    int32_t         *W_texture;
    int32_t         *E_texture;
    int32_t         *D_texture;
    t_point         *inter_arr;
    t_door          *door_arr;
    t_face          *face_lst;
    mlx_image_t     *map_img;
    mlx_image_t     *proj_img;
}               t_data;

void        ft_move_plr(int key, t_data *arg);
void        free_lnkd_lst(t_face *lst);
int         ft_door_ctl(t_data *data);
void        animation(t_data *data);
void        animate_plr(t_data *data);
void        ft_mouse(t_data *data);
int         init_gun(t_data *data);
int         ft_mini_map(t_data *data);
void        clean_up(t_data *data);
int32_t     *get_texture_arr(t_data *data, char *path);
void        delete_imgs(t_data *data, int size);
void        ft_cast_rays(t_data *data);
void        ft_clear_image(mlx_image_t *img);
char        **ft_split(char const *s, char c);
int         put_error(t_data *data, char *des, int set);
double      get_height(t_data *data, int i);
void        shut(t_data *data);
int         face_list(t_data *data);
mlx_image_t *load_image(t_data *data, char *path);
void        ft_render_wall(t_data *data);
void        fill_door_array(t_data *data);
t_door      *get_door(t_data *data, int i, int j);
double      real_angle(double angle);
int         ft_check_next(t_data *data, double angle);
void        ft_inter(t_data *data, t_point *inter, double angle);

# endif