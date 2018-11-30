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

int		key_hook(int keycode, t_window *win)
{
    printf("Key : %i", keycode);
	if (keycode == 'E')
		exit(EXIT_SUCCESS);
    else if (keycode == 'D')
        win->map->origin.x += 10;
    else if (keycode == 'A')
        win->map->origin.x -= 10;
    else if (keycode == 'S')
        win->map->origin.y += 10;
    else if (keycode == 'W')
        win->map->origin.y -= 10;
	/*if (keycode == || keycode == )
	{
		if (set_dots(win, win->inputs, win->map))
			return (0);
		printf("Fin set point\n");

		print_dots(win, win->inputs, win->map);
		printf("Fin print dot\n");
	}*/
	return (0);
}

int     mouse_hook(int button, int x, int y, t_window *win)
{
    if (button == 4)
    {
		win->map->zoom += 0.01;
    }
    else if (button == 5)
	{
        win->map->zoom -= 0.01;
    }
	return (0);
}