/* http://poj.org/problem?id=1287 */
/* AC 16MS 380K */
#include <stdio.h>
#include <string.h>

const int MAX_N = 50 + 10;

int prim(int mp[][MAX_N], int n)
{
	int i, j, k, min, ans;
	int book[MAX_N];
	int tree[MAX_N];
	int dist[MAX_N];

	for(i = 1; i < n; i++)
	{
		book[i] = 0;
		tree[i] = 0;
		dist[i] = mp[0][i];
	}
	book[0] = 1;
	tree[0] = -1;

	ans = 0;
	for(i = 1; i < n; i++)
	{
		min = 0x1f1f1f1f;
		k = -1;
		for(j = 1; j < n; j++)
		{
			if(book[j] == 0 && min > dist[j])
			{
				k = j;
				min = dist[j];
			}
		}
		if(k == -1)
		{
			return -1;
		}
		book[k] = 1;
		ans += mp[tree[k]][k];
		for(j = 1; j < n; j++)
		{
			if(book[j] == 0 && mp[k][j] < dist[j])
			{
				dist[j] = mp[k][j];
				tree[j] = k;
			}
		}
	}
	return ans;
}

int main()
{
	int n, m;
	int i, a, b, w, ans;
	int mp[MAX_N][MAX_N];

	while(scanf("%d", &n) != EOF && n > 0)
	{
		scanf("%d", &m);
		memset(mp, 0x1f, sizeof(mp));
		for(i = 0; i < m; i++)
		{
			scanf("%d %d %d", &a, &b, &w);
			a -= 1;
			b -= 1;
			if(w < mp[a][b])
			{
				mp[a][b] = w;
				mp[b][a] = w;
			}
		}

		ans = prim(mp, n);
		printf("%d\n", ans);
	}
	return 0;
}

/*
1 0

2 3
1 2 37
2 1 17
1 2 68

3 7
1 2 19
2 3 11
3 1 7
1 3 5
2 3 89
3 1 91
1 2 32

5 7
1 2 5
2 3 7
2 4 8
4 5 11
3 5 10
1 5 6
4 2 12

0

*/