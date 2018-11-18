/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/10 17:21:22 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/11 17:45:11 by agiordan    ###    #+. /#+    ###.fr     */
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
# include "get_next_line.h"

typedef struct	s_window
{
    void		*mlx;
    void		*win;
}				s_window;

typedef struct	s_dot
{
	float		x;
	float		y;
}				s_dot;

typedef struct	s_vector
{
	float	dx;
	float	dy;
}				s_vector;

typedef struct	s_inputs
{
	int		fd;
	char	*line;
	char	**tabstr;
	int		*tmp;
	int		**tab;
}				s_inputs;

typedef struct		s_map
{
	s_dot		origin;
	s_vector	i;
	s_vector	j;
	s_vector	k;
	s_dot		***tabdot;
	float		zoom;
}			s_map;

void			ft_put_line(s_window window, s_dot *d1, s_dot *d2, int color);

#endif
