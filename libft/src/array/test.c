#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char *tab[3] = {
		"Wesh",
		"fdp",
		NULL};
	char **newtab;

	newtab = ft_2dchardup(tab);
	printf("%d\n", (int)ft_2dcharlen(newtab));
	ft_2dchardel(&newtab);

	return (0);
}
