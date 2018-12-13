/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/10 17:21:22 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 22:03:35 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"

typedef struct	s_dot
{
	float		x;
	float		y;
}				t_dot;

typedef struct	s_par
{
	t_dot		d1;
	t_dot		d2;
	t_dot		d3;
	t_dot		d4;
}				t_par;

typedef struct	s_vector
{
	float	    x;
	float	    y;
}				t_vector;

typedef struct	s_inputs
{
	int		    fd;
	char	    *line;
	char	    **tabstr;
	int		    lenx;
	int		    leny;
	int		    *tmp;
	int		    **tab;
}				t_inputs;

typedef struct	s_map
{
	t_dot		origin;
	t_dot		centre;
	t_vector	i;
	t_vector	j;
	t_vector	k;
	t_dot		***tabdot;
	float		zoom;
}			    t_map;

typedef struct	s_window
{
    void		*mlx;
    void		*win;
	int			width;
	int			height;
	char		*name;
	t_map		*map;
	t_inputs	*inputs;
}				t_window;

void			ft_put_line(t_window *window, t_dot *d1, t_dot *d2, int color);
void			ft_put_par(t_window *win, t_par par, int color);
int				set_dots(t_window *win, t_inputs *inputs, t_map *map);
void			print_dots(t_window *win, t_inputs *inputs, t_map *map);
t_par			set_par(t_dot *d1, t_dot *d2, t_dot *d3, t_dot *d4);
int				key_hook(int keycode, t_window *win);
int     		mouse_hook(int button, int x, int y, t_window *win);
void			ft_refresh(t_window *win);
void			reset_dots(t_window *win, t_inputs *inputs, t_map *map);
void			ft_print_bordure(t_window *win);

#endif
