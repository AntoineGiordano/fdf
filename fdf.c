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

#include "fdf.h"

void	ft_set_null(t_window *win, t_inputs *inputs, t_image *image)
{
	win->mlx = NULL;
	win->win = NULL;
	win->name = NULL;
	inputs->line = NULL;
	inputs->tabline = NULL;
	inputs->tmpcolors = NULL;
	inputs->colors = NULL;
	inputs->tmptab = NULL;
	inputs->tab = NULL;
	image->image_ptr = NULL;
	image->image = NULL;
}

int		ft_clear_memory(t_window *win, t_inputs *inputs) //free 3 void *
{
	if (win->win)
		mlx_destroy_window(win->mlx, win->win);
	if (win->map->image->image_ptr)
	{
		mlx_destroy_image(win->mlx, win->map->image->image_ptr);
		free(win->map->image->image_ptr);
	}
	ft_strdel(&(win->map->image->image));
	reset_dots(win, win->inputs, win->map);
	ft_strdel(&(win->name));
	ft_strdel(&(inputs->line));
	ft_tabdel(&(inputs->tabline));
	ft_tabintdel(&(inputs->tmpcolors));
	ft_tabint2del(&(inputs->colors), win->height);
	ft_tabintdel(&(inputs->tmptab));
	ft_tabint2del(&(inputs->tab), win->height);
	free(win->map->image);
	free(win->map);
	free(win->inputs);
	free(win);
	return (0);
}

int		ft_init_tabdot(t_window *win, t_inputs *inputs, t_map *map)
{
	int	i;
	int	j;

	if (!(map->tabdot = (t_dot ***)malloc(sizeof(t_dot **) * (inputs->leny + 1))))
		return (1);
	printf("Fin malloc\n");
	map->tabdot[inputs->leny] = NULL;
	i = -1;
	while (++i < inputs->leny)
	{
		printf("New line\n");
		if (!(map->tabdot[i] = (t_dot **)malloc(sizeof(t_dot *) * (inputs->lenx + 1))))
			return (1);
		map->tabdot[i][inputs->lenx] = NULL;
		j = -1;
		while (++j < inputs->lenx)
			if (!(map->tabdot[i][j] = (t_dot *)malloc(sizeof(t_dot))))
				return (1);
	}
	return (0);
}

int		ft_init(t_window *win, t_inputs *inputs, t_map *map, t_image *image)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	win->map->image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = mlx_get_data_addr(image->image_ptr,
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
	map->centre.x = win->inputs->lenx / 2 - ((win->inputs->lenx % 2) ? 0 : 0.5);
	map->centre.y = win->inputs->leny / 2 - ((win->inputs->leny % 2) ? 0 : 0.5);
	if (ft_init_tabdot(win, inputs, map))
		return (1);
	return (0);
}

int		main(int ac, char **av)
{
	t_window	win;
	t_map		map;
	t_image		image;
	t_inputs	inputs;
	int			ifile;
	
	if (ac == 1)
		ft_putstr("usage: [-name window's_name] | [-len width height] file\n");
	else
	{
		win.inputs = &inputs;
		win.map = &map;
		win.map->image = &image;
		if ((ifile = ft_params(&win, ac, av)) == -1)
			return (ft_clear_memory(&win, &inputs)); 
		//printf("Fin check params\n");
		ft_set_null(&win, &inputs, &image);
		if (ft_parse(&inputs, av[ifile]))
			return (ft_clear_memory(&win, &inputs));
		//printf("Fin set parse\n");
		if (ft_init(&win, win.inputs, win.map, win.map->image))
			return (ft_clear_memory(&win, &inputs));
		//printf("Fin set init\n");
		ft_refresh(&win, win.map->image);
		mlx_mouse_hook(win.win, mouse_hook, &win);
		mlx_key_hook(win.win, key_hook, &win);
		mlx_loop(win.mlx);
	}
	return (0);
}

/*win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 1000, 1000, "gv");
	t_dot d1;
	t_dot d2;
	d1.x = 100;
	d2.x = 900;
	d1.y = 100;
	d2.y = 900;
	d1.color.r = ft_atoi_base("50BB50", 16) / (16 * 16 * 16 * 16);
	d1.color.g = (ft_atoi_base("50BB50", 16) % (16 * 16 * 16 * 16)) / (16 * 16);
	d1.color.b = ft_atoi_base("50BB50", 16) % (16 * 16);

	d2.color.r = ft_atoi_base("5050FF", 16) / (16 * 16 * 16 * 16);
	d2.color.g = (ft_atoi_base("5050FF", 16) % (16 * 16 * 16 * 16)) / (16 * 16);
	d2.color.b = ft_atoi_base("5050FF", 16) % (16 * 16);
	
	printf("RGB 1 : %f, %f, %f\n", d1.color.r, d1.color.g, d1.color.b);
	printf("RGB 2 : %f, %f, %f\n", d2.color.r, d2.color.g, d2.color.b);
			
	ft_put_line(&win, &d1, &d2);
	mlx_loop(win.mlx);*/



//ATTENTION FICHIERS INVALIDE

//Couleur ?..
//Zoom
//Translation fleches
//Options
//	-	Taille fenetre
//	-	Nom fenetre
//Centres
//echo $? pour retour de la derniere commande