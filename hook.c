/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hook.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/25 02:12:04 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 02:12:06 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	ft_refresh(t_window *win, t_image *image)
{
	set_dots(win, win->inputs, win->map);
	mlx_clear_window(win->mlx, win->win);
	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	print_dots(win, win->inputs, win->map);
	mlx_put_image_to_window(win->mlx, win->win, win->map->image->image_ptr, 0, 0);
}

int		key_hook(int keycode, t_window *win)
{
    if (keycode == 53)
	{
		ft_clear_memory(win, win->inputs);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 124)
		win->map->origin.x += 15;
	else if (keycode == 123)
		win->map->origin.x -= 15;
	else if (keycode == 125)
		win->map->origin.y += 15;
    else if (keycode == 126)
		win->map->origin.y -= 15;
	ft_parallele(win, keycode);
	ft_refresh(win, win->map->image);
	return (0);
}

int     mouse_hook(int button, int x, int y, t_window *win)
{
    if (button == 4)
	win->map->zoom -= 0.06;
    else if (button == 5)
        win->map->zoom += 0.06;
	if (win->map->zoom < 0)
		win->map->zoom = 0;
	if (button == 4 || button == 5)
		ft_refresh(win, win->map->image);
	return (0);
}

