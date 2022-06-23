#include<stdio.h>
#include "./include/pipex.h"

int main(int argc, char **argv, char **envp)
{
	int i = 0;
	char **str;

	str = ft_split(argv[1], ' ');
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	
}