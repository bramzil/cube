# include "cube.h"

typedef struct  s_line
{
    float       x;
    float       y;
    float       inc_x;
    float       inc_y;   
}               t_line;

static int  ft_is_wall(t_data *data, float x, float y)
{
    if (data->map[(int)(y / 50)][(int)(x / 50)] == '1')
        return (1);
    return (0);
}


static void  ft_get_steps(t_data *data, t_line *line, float angle)
{
    float       d_x;
    float       d_y;
    float       steps;

    d_x = 20 * cos(angle);
    d_y = 20 * sin(angle * -1);
    steps = abs((int)d_x);
    if (abs((int)d_x) < abs((int)d_y))
        steps = abs((int)d_y);
    line->inc_x = (float)(d_x / steps);
    line->inc_y = (float)(d_y / steps);
}

static int ft_draw_line(t_data *data, float angle)
{
    int         hypo;
    t_line      line;

    line.x = data->plr->x;
    line.y = data->plr->y;
    ft_get_steps(data, &line, angle);
    while ((0 < line.x) && (line.x < 500) && \
        (0 < line.y) && (line.y < 500))
    {
        if (ft_is_wall(data, line.x, line.y))
            break ;
        mlx_put_pixel(data->rays_img, line.x, \
            line.y, 0xffff00f0);
        line.x += line.inc_x;
        line.y += line.inc_y;
    }
    hypo = sqrt((line.x * line.x) + \
        (line.y * line.y));
    return (hypo);
}

void    ft_drop_rays(t_data *data)
{
    int     i;
    float   rad;
    float   incr;
    float   start;

    i = 500;
    rad = (M_PI / 180);
    incr = ((60 * rad) / 500);
    start = ((data->plr->d - 30) + 360 * \
        (data->plr->d - 30 < 0)) * rad;
    while (i--)
    {
        ft_draw_line(data, start);
        start += incr;
    }
}