/* http://poj.org/problem?id=1679 */
#include <stdio.h>
#include <string.h>

const int MAX_N = 100 + 5;

int n, m;
int mp[MAX_N][MAX_N];

int solve()
{
	return -1;
}

int main()
{
	int t, i, x, y, w, ans;

	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d", &n, &m);
		memset(mp, 0x1f, sizeof(mp));
		for(i = 0; i < m; i++)
		{
			scanf("%d %d %d", &x, &y, &w);
			if(mp[x][y] > w)
			{
				mp[x][y] = w;
				mp[y][x] = w;
			}
		}

		ans = solve();
		if(ans < 0)
		{
			printf("Not Unique!\n");
		}
		else
		{
			printf("%d\n", ans);
		}
	}
	return 0;
}

/*
2
3 3
1 2 1
2 3 2
3 1 3
4 4
1 2 2
2 3 2
3 4 2
4 1 2

3
Not Unique!

*/