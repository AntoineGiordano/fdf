/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/10 17:21:09 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 16:38:10 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
**	Couleur fichier
**	Palette couleur en parametres
**	Zoom
**	Translation fleches
**	Options
**		-	Taille fenetre
**		-	Nom fenetre
**		-   palette couleur
**	Centres
**	Fichier difforme
*/

#include "fdf.h"

void	ft_set_null(t_window *win, t_inputs *inputs, t_image *image)
{
	win->mlx = NULL;
	win->win = NULL;
	win->map->minz = 0;
	win->map->maxz = 0;
	inputs->line = NULL;
	inputs->tab = NULL;
	image->image_ptr = NULL;
	win->map->tabdot = NULL;
}

int		ft_clear_memory(t_window *win, t_inputs *inputs)
{
	int	i;

	if (win->win)
		mlx_destroy_window(win->mlx, win->win);
	else
	{
		ft_putstr("usage: [-name <name>] | [-len <width> <height>] | ");
		ft_putstr("[-color <min_color> <max_color>] file\n");
	}
	if (win->map->image->image_ptr)
		mlx_destroy_image(win->mlx, win->map->image->image_ptr);
	reset_dots(win, win->inputs, win->map);
	if (inputs->line)
		ft_strdel(&(inputs->line));
	if (inputs->tab)
	{
		i = -1;
		while (++i < inputs->leny)
			ft_tabintdel(&(inputs->tab[i]));
	}
	close(inputs->fd);
	return (0);
}

int		ft_init_tabs(t_window *win, t_inputs *inputs, t_map *map)
{
	int	i;
	int	j;

	if (!(map->tabdot = (t_dot ***)malloc(sizeof(t_dot **) *
	(inputs->leny + 1))))
		return (1);
	if (!(inputs->tab = (int **)malloc(sizeof(int *) * inputs->leny)))
		return (1);
	map->tabdot[inputs->leny] = NULL;
	i = -1;
	while (++i < inputs->leny)
	{
		if (!(map->tabdot[i] = (t_dot **)malloc(sizeof(t_dot *) *
		(inputs->lenx[i] + 1))))
			return (1);
		map->tabdot[i][inputs->lenx[i]] = NULL;
		if (!(inputs->tab[i] = (int *)malloc(sizeof(int) * inputs->lenx[i])))
			return (1);
		j = -1;
		while (++j < inputs->lenx[i])
			if (!(map->tabdot[i][j] = (t_dot *)malloc(sizeof(t_dot))))
				return (1);
	}
	return (0);
}

int		ft_init(t_window *win, t_inputs *inputs, t_map *map, t_image *image)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	map->zoom = 1.5;
	map->origin.x = win->width / 2;
	map->origin.y = win->height / 2;
	map->i.x = map->zoom * 10;
	map->i.y = map->zoom * 4;
	map->j.x = map->zoom * (-10);
	map->j.y = map->zoom * 4;
	map->k.x = map->zoom * 0;
	map->k.y = map->zoom * (-10.7);
	map->centre.x = inputs->lenx[(int)(inputs->leny / 2)] / 2 -
					((inputs->lenx[(int)(inputs->leny / 2)] % 2) ? 0 : 0.5);
	map->centre.y = inputs->leny / 2 - ((inputs->leny % 2) ? 0 : 0.5);
	return (0);
}

int		main(int ac, char **av)
{
	t_window	win;
	t_map		map;
	t_image		image;
	t_inputs	inputs;
	int			ifile;

	win.inputs = &inputs;
	win.map = &map;
	win.map->image = &image;
	ft_set_null(&win, &inputs, &image);
	if ((ifile = params(&win, ac, av)) == -1)
		return (ft_clear_memory(&win, &inputs));
	if (parse(&win, &inputs, av[ifile]))
		return (ft_clear_memory(&win, &inputs));
	if (ft_init(&win, win.inputs, win.map, win.map->image))
		return (ft_clear_memory(&win, &inputs));
	ft_refresh(&win, win.map->image);
	mlx_mouse_hook(win.win, mouse_hook, &win);
	mlx_key_hook(win.win, key_hook, &win);
	mlx_loop(win.mlx);
	return (0);
}
