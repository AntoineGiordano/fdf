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

int		ft_params(t_window *win, int ac, char **av)
{
	int			i;
	int			ifile;

	i = 0;
	ifile = -1;
	win->name = ft_strdup("Fdf");
	win->width = 1000;
	win->height = 1000;
	printf("Nombre params : %i\n", ac);
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-name"))
		{
			if (i + 1 < ac)
				win->name = av[i + 1];
		}
		else if (!ft_strcmp(av[++i], "-len"))
		{
			if (i + 1 < ac)
				win->width = ft_atoi(av[i++ + 1]);
			if (i + 1 < ac)
				win->height = ft_atoi(av[i++ + 2]);
		}
		else
			ifile = i;
	}
	return (ifile);
}

int		ft_parse_2(t_inputs *inputs, int *count, int *nline)
{
	char	*line;
	int		j;

	inputs->tabline = ft_strsplit(inputs->line, ' ');
	*count = ft_tablen(inputs->tabline);
	if (!(inputs->tmptab = (int *)malloc(sizeof(int) * *count)))
		return (1);
	if (!(inputs->tmpcolors = (int *)malloc(sizeof(int) * *count)))
		return (1);
	ft_filltabint(&(inputs->tmpcolors), *count, ft_atoi_base("FFFFFF", 16));
	j = -1;
	while (++j < *count)
	{
		line = inputs->tabline[j];
		inputs->tmptab[j] = ft_atoi(inputs->tabline[j]);
		if (ft_strlen(line) != ft_nbrlen(ft_atoi(line)))
			inputs->tmpcolors[j] = ft_atoi_base(ft_strsub(line, ft_nbrlen(ft_atoi(line)) + 3, ft_strlen(line) - ft_nbrlen(ft_atoi(line)) - 3), 16);
	}
	inputs->tab = ft_addinttab(inputs->tab, inputs->tmptab, *nline);
	inputs->colors = ft_addinttab(inputs->colors, inputs->tmpcolors, *nline);
	return (0);
}

int		ft_parse(t_inputs *inputs, char *file)
{
	//gnl - split - nb de cases - malloc tabint - convertir char/int - addinttab -
	int		count;
	int		ret;
	int		nline;

	if ((inputs->fd = open(file, O_RDONLY)) == -1)
		return (1);
	if (!(inputs->tab = (int **)malloc(sizeof(int *))))
		return (1);
	if (!(inputs->colors = (int **)malloc(sizeof(int **))))
		return (1);
	printf("Fin malloc tab & line\n");
	nline = 0;
	ret = 1;
	while ((ret = get_next_line(inputs->fd, &(inputs->line))) == 1)
	{
		if (ft_parse_2(inputs, &count, &nline))
			return (1);
		nline++;
	}
	inputs->lenx = count;
	inputs->leny = nline;
	return (0);
}
