/* http://poj.org/problem?id=1287 */
/* AC 16MS 400K */
#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAX_N = 50 + 10;

int main()
{
	int n, m;
	int i, a, b, w, ans;

	while(scanf("%d", &n) != EOF && n > 0)
	{
		scanf("%d", &m);
		for(i = 0; i < m; i++)
		{
			scanf("%d %d %d", &a, &b, &w);
		}

		
		printf("%d\n", ans);
	}
	return 0;
}