# include "cube.h"

static void get_dir(double angle, int *x_dir, int *y_dir)
{
    *x_dir = 1 - (2 * ((M_PI / 2) < angle && \
        angle < (M_PI + (M_PI / 2))));
    *y_dir = 1 - (2 * (0 < angle && angle < M_PI));
}

static int  is_wall(t_data *data, t_point *point, int x_d, int y_d)
{
    int         i;
    int         j;

    i = (point->x / data->grd_ht) - \
        (1 * (x_d < 0));
    j = (point->y / data->grd_wd) - \
        (1 * (y_d < 0));
    if ((point->x < 0) || (point->y < 0) || \
        ((data->grd_wd * 10) < point->x) || \
        ((data->grd_ht * 10) < point->y))
        return (1);
    else if (data->map[j][i] != '0')
        return (1);
    return (0);
}

static double hor_inter(t_data *data, t_point *inter, double angle)
{
    int         x_dir;
    int         y_dir;
    int         grd_ht;
    double      adja;
    double      oppo;

    grd_ht = data->grd_ht;
    get_dir(angle, &x_dir, &y_dir);
    inter->y = (int)(data->plr.y / grd_ht) * grd_ht;
    while ((0 < inter->y) && (inter->y < \
        (data->grd_ht * 10)))
    {
        if (((0 < y_dir) && (data->plr.y < inter->y)) || \
            ((y_dir < 0) && (inter->y < data->plr.y)))
        {
            oppo = fabs(data->plr.y - inter->y);
            adja = fabs(oppo / tan(angle));
            inter->x = data->plr.x + (x_dir  * adja);
            if (is_wall(data, inter, 0, y_dir))
                break ;
        }
        inter->y += (y_dir * grd_ht);
    }
    return (sqrt((adja * adja) + (oppo * oppo)));
}

static double ver_inter(t_data *data, t_point *inter, double angle)
{
    int         x_dir;
    int         y_dir;
    int         grd_wd;
    double      adja;
    double      oppo;

    grd_wd = data->grd_wd;
    get_dir(angle, &x_dir, &y_dir);
    inter->x = (int)(data->plr.x / grd_wd) * grd_wd;
    while ((0 < inter->x) && (inter->x < \
        (data->grd_wd * 10)))
    {
        if (((0 < x_dir) && (data->plr.x < inter->x)) || \
            ((x_dir < 0) && (inter->x < data->plr.x)))
        {
            adja = fabs(data->plr.x - inter->x);
            oppo = fabs(adja * tan(angle));
            inter->y = data->plr.y + (y_dir * oppo);
            if (is_wall(data, inter, x_dir, 0))
                break ;
        }
        inter->x += (x_dir * grd_wd);
    }
    return (sqrt((adja * adja) + (oppo * oppo)));
}

double  ft_get_inter(t_data *data, t_point *inter, double angle)
{
    double      tmp;
    double      dist;
    t_point     h_inter;
    t_point     v_inter;

    tmp = hor_inter(data, &h_inter, angle);
    dist = ver_inter(data, &v_inter, angle);
    if (tmp <= dist)
    {
        (inter->x = h_inter.x, inter->y = h_inter.y);
        dist = tmp;
    }
    else
        (inter->x = v_inter.x, inter->y = v_inter.y);
    return (dist);
}
