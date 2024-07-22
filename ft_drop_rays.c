# include "cube.h"

static int  ft_is_wall(t_data *data, double x, double y)
{
    if ((data->map[(int)((y + 1) / 20)][(int)(x / 20)] == '1') || \
        (data->map[(int)((y - 1) / 20)][(int)(x / 20)] == '1') || \
        (data->map[(int)(y / 20)][(int)((x + 1) / 20)] == '1') || \
        (data->map[(int)(y / 20)][(int)((x - 1) / 20)] == '1'))
        return (1);
    return (0);
}


static void  ft_get_steps(t_data *data, t_line *line, double angle)
{
    double       d_x;
    double       d_y;
    double       steps;

    d_x = 20 * cos(angle);
    d_y = 20 * sin(angle * -1);
    steps = fabs(d_x);
    if (fabs(d_x) < fabs(d_y))
        steps = fabs(d_y);
    line->inc_x = (double)(d_x / steps);
    line->inc_y = (double)(d_y / steps);
}

static double ft_draw_line(t_data *data, double angle, int i)
{
    double         oppo;
    double         adja;
    t_line         line;

    line.x = data->plr->x;
    line.y = data->plr->y;
    ft_get_steps(data, &line, angle);
    while ((0 < line.x) && (line.x < 200) && \
        (0 < line.y) && (line.y < 200))
    {
        if (ft_is_wall(data, line.x, line.y))
            break ;
        mlx_put_pixel(data->rays_img, line.x, \
            line.y, 0xffff000f);
        line.x += line.inc_x;
        line.y += line.inc_y;
    }
    data->array[i].x = line.x;
    data->array[i].y = line.y; 
    oppo = fabs(data->plr->x - line.x);
    adja = fabs(data->plr->y - line.y);
    return (sqrt((oppo * oppo) + (adja * adja)));
}

void    ft_drop_rays(t_data *data)
{
    double  x;
    double  dst;
    double  incr;
    double  start;
    double  rad;

    x = 760;
    rad = (M_PI / 180);
    incr = ((60 * rad) / 760);
    start = ((data->plr->d - 30) + 360 * \
        (data->plr->d - 30 < 0)) * rad;
    while (0 <= --x)
    {
        dst = ft_draw_line(data, start, x);
        ft_render_line(data, dst, x);
        start += incr;
    }
    int i = -1;
    while (++i < 760)
        printf("point: %d, x: %f, y: %f\n", i, data->array[i].x, data->array[i].y);
}