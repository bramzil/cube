# include "cube.h"

void    free_2d_arr(char **arr)
{
    int     i;

    i = -1;
    while (arr && arr[++i])
        free (arr[1]);
    free(arr);
}

void    free_lnkd_lst(t_face *lst)
{
    t_face      *tmp;
    
    while (lst && lst->next)
    {
        tmp = lst;
        lst = lst->next;
        free (tmp);
    }
}

void    delete_imgs(t_data *data, int size)
{
    int         i;

    i = -1;
    while (++i < size)
        mlx_delete_image(data->mlx, data->gun.arr[i]);
    mlx_delete_image(data->mlx, data->proj_img);
    mlx_delete_image(data->mlx, data->map_img);
}

void    free_map_text(t_data *data)
{
    free(data->N_texture);
    free(data->S_texture);
    free(data->W_texture);
    free(data->E_texture);
    free(data->D_texture);
    free_2d_arr(data->map);
}

void    clean_up(t_data *data)
{
    free_map_text(data);
    free(data->door_arr);
    free(data->inter_arr);
    delete_imgs(data, 13);
    mlx_terminate(data->mlx);
    free_lnkd_lst(data->face_lst);
    exit(0);
}