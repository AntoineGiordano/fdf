/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_set_line.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/12 14:59:37 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/12 14:59:38 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

float	ft_abs(float x)
{
	if (x >= 0)
		return (x);
	else
		return (-x);
}

void	set_pixel(t_window *win, int x, int y, int color)
{
	if ((x > 0 && x < win->width) && (y > 0 && y < win->height))
		win->map->image->image[x + y * win->width] = color;
}

void	ft_put_line(t_window *win, t_dot *d1, t_dot *d2)
{
	t_vector	pas;
	int			nbpixels;
	int			i;
	int			color;

	//printf("Debut put line\n");
	pas.x = d2->x - d1->x;
	pas.y = d2->y - d1->y;
	if (ft_abs(pas.x) > ft_abs(pas.y))
	{
		nbpixels = ft_abs(pas.x);
		pas.y /= ft_abs(pas.x);
		pas.x /= ft_abs(pas.x);
	}
	else
	{
		nbpixels = ft_abs(pas.y);
		pas.x /= ft_abs(pas.y);
		pas.y /= ft_abs(pas.y);
	}
	//printf("RGB1 : %#x\t RGB2 : %#x\n", d1->color, d2->color);
	i = -1;
	while (++i < nbpixels)
	{
		color = maping(win, d1->color, d2->color, (double)i / (double)nbpixels);
		//printf("Color pixel : %#x\n", color);
		set_pixel(win, d1->x + pas.x * i, d1->y + pas.y * i, color);
	}
} // Test avec directement i / nbpixels * diffx

/*
void	set_pas(t_dot d2, t_dot d3, t_vector *pas, int *nbpixels)
{
	pas->x = d3.x - d2.x;
	pas->y = d3.y - d2.y;
	if (ft_abs(pas->x) > ft_abs(pas->y))
	{
		*nbpixels = ft_abs(pas->x);
		pas->y /= ft_abs(pas->x);
		pas->x /= ft_abs(pas->x);
	}
	else
	{
		*nbpixels = ft_abs(pas->y);
		pas->x /= ft_abs(pas->y);
		pas->y /= ft_abs(pas->y);
	}
}

void	ft_put_par(t_window *win, t_par par, int color)
{
	t_dot		tmp;
	t_vector	pas;
	t_vector	line;
	int			nbpixels;
	int			i;

	line.x = par.d1.x - par.d2.x;
	line.y = par.d1.y - par.d2.y;
	set_pas(par.d2, par.d3, &pas, &nbpixels);
	i = -1;
	while (i++ < nbpixels)
	{
		tmp.x = par.d2.x + line.x;
		tmp.y = par.d2.y + line.y;
		tmp.color = color;
		par.d2.x += pas.x;
		par.d2.y += pas.y;
		par.d2.color = color;
		ft_put_line(win, &(par.d2), &tmp);
	}
}*/
