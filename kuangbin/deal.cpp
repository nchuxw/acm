#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fpi, *fpo;
	char str[1000], addr[1000];
	int len;

	fpi = fopen("./kuangbin/problem.txt", "r+");
	fpo = fopen("./kuangbin/problem_o.txt", "w+");
	while(fgets(str, 1000, fpi) != NULL)
	{
		// printf("%s", str);
		len = strlen(str);
		str[len - 1] = '\0';
		if(str[0] == 'H' && str[1] == 'D' && str[2] == 'U')
		{
			strcpy(addr, "  http://acm.hdu.edu.cn/showproblem.php?pid=");
			len = strlen(addr);
			memcpy(addr + len, str + 4, 4);
			addr[len + 4] = '\0';
			len = strlen(str);
			strcpy(str + len, addr);
		}
		if(str[0] == 'P' && str[1] == 'O' && str[2] == 'J')
		{
			strcpy(addr, "  http://poj.org/problem?id=");
			len = strlen(addr);
			memcpy(addr + len, str + 4, 4);
			addr[len + 4] = '\0';
			len = strlen(str);
			strcpy(str + len, addr);
		}
		fprintf(fpo, "%s\n", str);
	}
	return 0;
}