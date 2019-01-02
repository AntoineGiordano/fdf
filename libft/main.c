/*HEADER*/

#include "libft.h"
#include "stdio.h"
#include "stdlib.h"

int main(void)
{
	char **tab;
	
	tab = ft_tabnew(16, 35);
	tab[0][0] = '8';
	tab[0][1] = '9';
	
	ft_printtab(tab, ft_tablen(tab));
	
	ft_tabdel(&tab);
	ft_putendl("Fin");
	//ft_printtab(tab, ft_tablen(tab));

	return (0);
}
