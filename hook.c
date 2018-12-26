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

void	ft_parallele_x(t_window *win, int sign)
{
	if (sign == 1)
	{
		win->map->i.x = 0;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = -10;
		win->map->k.x = 10;
		win->map->k.y = 0;
	}
	else
	{
		win->map->i.x = 0;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = -10;
		win->map->k.x = -10;
		win->map->k.y = 0;
	}
}

void	ft_parallele_y(t_window *win, int sign)
{
	if (sign == 1)
	{
		win->map->i.x = 10;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = 0;
		win->map->k.x = 0;
		win->map->k.y = -10;
	}
	else
	{
		win->map->i.x = 10;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = 0;
		win->map->k.x = 0;
		win->map->k.y = 10;
	}
}

void	ft_parallele_z(t_window *win, int sign)
{
	if (sign == 1)
	{
		win->map->i.x = -10;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = -10;
		win->map->k.x = 0;
		win->map->k.y = 0;
	}
	else
	{
		win->map->i.x = 10;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = -10;
		win->map->k.x = 0;
		win->map->k.y = 0;
	}
}

void	ft_parallele(t_window *win)
{
/*	if (keycode == )
		ft_parallele_x(win, -1);	
	else if (keycode == )
		ft_parallele_x(win, 1);	
	else if (keycode == )
		ft_parallele_y(win, -1);	
	else if (keycode == )
		ft_parallele_y(win, 1);	
	else if (keycode == )
		ft_parallele_z(win, -1);	
	else if (keycode == )
		ft_parallele_z(win, 1);*/
}

void	ft_refresh(t_window *win)
{
	reset_dots(win, win->inputs, win->map);
	if (set_dots(win, win->inputs, win->map))
		exit(EXIT_FAILURE);
	printf("Fin set dots\n");

	mlx_clear_window(win->mlx, win->win);
	print_dots(win, win->inputs, win->map);
	printf("Fin print dot\n");
}

int	key_hook(int keycode, t_window *win)
{
	printf("Key : %i\n", keycode);
    	if (keycode == 53)
	{
		mlx_destroy_window(win->mlx, win->win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 124)
		win->map->origin.x -= 15;
	else if (keycode == 123)
		win->map->origin.x += 15;
	else if (keycode == 125)
		win->map->origin.y -= 15;
    	else if (keycode == 126)
		win->map->origin.y += 15;
	//ft_parallele(win);
	ft_refresh(win);
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
		ft_refresh(win);
	return (0);
}

