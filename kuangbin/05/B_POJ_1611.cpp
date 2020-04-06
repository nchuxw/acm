/* http://poj.org/problem?id=1611 */
#include <stdio.h>

const int MAX_N = 30000 + 10;
const int MAX_M = 500 + 10;

int main()
{
	int n, m;
	int i, j, k, num;

	while(scanf("%d %d", &n, &m) != EOF && (n != 0 || m != 0))
	{
		for(i = 0; i < m; i++)
		{
			scanf("%d", &k);
			for(j = 0; j < k; j++)
			{
				scanf("%d", &num);
			}
		}
	}
	return 0;
}