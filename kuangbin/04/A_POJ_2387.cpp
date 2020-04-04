/* http://poj.org/problem?id=2387 */
/* AC 47MS 4332K */
#include <stdio.h>
#include <string.h>

const int MAX_N = 1000 + 10;

int n;
int mp[MAX_N][MAX_N];

int dijkstra(int start, int end)
{
	int i, j, k, min;
	int book[MAX_N];
	int dist[MAX_N];

	for(i = 0; i <= n; i++)
	{
		dist[i] = mp[start][i];
		book[i] = 0;
	}
	dist[start] = 0;
	book[start] = 1;

	for(i = 1; i < n; i++)
	{
		min = 0x1f1f1f1f;
		for(j = 0; j < n; j++)
		{
			if(book[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}
		if(k == end)
		{
			return dist[k];
		}
		book[k] = 1;
		for(j = 0; j < n; j++)
		{
			if(book[j] == 0 && dist[j] > dist[k] + mp[k][j])
			{
				dist[j] = dist[k] + mp[k][j];
			}
		}
	}
	return -1;
}

int main()
{
	int t, a, b, w;
	int i, ans;

	while(scanf("%d %d", &t, &n) != EOF)
	{
		memset(mp, 0x1f, sizeof(mp));
		for(i = 0; i < t; i++)
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
		ans = dijkstra(n - 1, 0);
		printf("%d\n", ans);
	}
	return 0;
}