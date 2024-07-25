# include "cube.h"

void ft_door_ctl(void *par)
{
    t_data      *data;

    data = (t_data *)par;
    if (data->door.counter <= 0)
    {
        if (data->door.state == 'N')
        {
            if (10 < data->door.var)
            {
                data->door.var -= 1;
                ft_clear_image(data->ddd__img);
                ft_cast_rays(data);
            }
            else
                data->door.state = 'O';
        }
        else if (data->door.state == 'S')
        {
            if (data->door.var < 32)
            {
                data->door.var += 1;
                ft_clear_image(data->ddd__img);
                ft_cast_rays(data);
            }
            else
                data->door.state = 'C';
        }
        data->door.counter = 10;
    }
    data->door.counter--;
}