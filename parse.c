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

int		flags(t_window *win, int ac, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-name"))
	{
		if (*i + 1 < ac)
			win->name = av[(*i)++ + 1];
	}
	else if (!ft_strcmp(av[*i], "-len"))
	{
		if (*i + 1 < ac)
			win->width = ft_atoi(av[++(*i)]);
		if (*i + 1 < ac)
			win->height = ft_atoi(av[++(*i)]);
	}
	else if (!ft_strcmp(av[*i], "-color"))
	{
		win->colorparam = 1;
		if (*i + 1 < ac)
			win->mincolor = ft_atoi_base(av[++(*i)], 16);
		if (*i + 1 < ac)
			win->maxcolor = ft_atoi_base(av[++(*i)], 16);
	}
	else
		return (1);
	return (0);
}

int		params(t_window *win, int ac, char **av)
{
	int	i;
	int	ifile;

	i = 1;
	ifile = -1;
	win->colorparam = 0;
	win->name = "Fdf";
	win->width = 1000;
	win->height = 1000;
	win->maxcolor = 0x50BB50;
	win->mincolor = 0xFFFFFF;
	while (i < ac)
	{
		if (flags(win, ac, av, &i))
			ifile = i;
		i++;
	}
	return (ifile);
}

int		set_size(t_window *win, t_inputs *inputs, char *file)
{
	char	*line;
	char	**tab;
	int		nline;
	int		fd;
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (1);
	inputs->lenx = NULL;
	nline = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ret == -1)
			return (1);
		inputs->lenx = ft_addint(inputs->lenx,
		ft_tablen(tab = ft_strsplit(line, ' ')), nline++);
		ft_tabdel(&tab);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	inputs->leny = nline;
	close(fd);
	return (0);
}

int		parse_2(t_window *win, char **tab, int nline, int j)
{
	if (!ft_isdigit(tab[j][0]) && tab[j][0] != '-' && tab[j][0] != '+')
		return (1);
	win->inputs->tab[nline][j] = ft_atoi(tab[j]);
	if (win->inputs->tab[nline][j] > win->map->maxz)
		win->map->maxz = win->inputs->tab[nline][j];
	else if (win->inputs->tab[nline][j] < win->map->minz)
		win->map->minz = win->inputs->tab[nline][j];
	if (!(win->colorparam))
	{
		win->map->tabdot[nline][j]->color = 16777215;
		if (ft_strstr(tab[j], ",0x"))
			win->map->tabdot[nline][j]->color =
			ft_atoi_base(ft_strstr(tab[j], ",0x") + 3, 16);
	}
	return (0);
}

int		parse(t_window *win, t_inputs *inputs, char *file)
{
	int		ret;
	int		nline;
	int		j;
	char	**tab;

	if (set_size(win, inputs, file) || ft_init_tabs(win, inputs, win->map))
		return (1);
	if ((inputs->fd = open(file, O_RDONLY)) == -1)
		return (1);
	nline = 0;
	while ((ret = get_next_line(inputs->fd, &(inputs->line)) == 1))
	{
		if (ret == -1)
			return (1);
		tab = ft_strsplit(inputs->line, ' ');
		j = -1;
		while (++j < inputs->lenx[nline])
			parse_2(win, tab, nline, j);
		ft_tabdel(&tab);
		ft_strdel(&(inputs->line));
		nline++;
	}
	colors(win, inputs, win->map);
	close(inputs->fd);
	return (0);
}
