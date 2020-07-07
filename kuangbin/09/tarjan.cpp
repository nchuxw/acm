/* vis_tarjan算法求强连通分量的个数 */
#include <stdio.h>
#include <string.h>

const int MAX_N = 100 + 10;

int n, m;
int mp[MAX_N][MAX_N];
int vis[MAX_N], vis_t;
int st[MAX_N], st_top;
int in_st[MAX_N];
int low[MAX_N];

int tarjan(int v)
{
	int i, k;

	vis[v] = vis_t;
	low[v] = vis_t;
	vis_t++;
	st_top++;
	st[st_top] = v;
	in_st[v] = 1;
	for(i = 1; i <= n; i++)
	{
		if(mp[v][i] == 0)
		{
			continue;
		}
		if(vis[i] == -1)
		{
			tarjan(i);
			if(low[v] > low[i])
			{
				low[v] = low[i];
			}
		}
		else if(in_st[i] == 1 && low[v] > vis[i])
		{
			low[v] = vis[i];
		}
	}
	if(low[v] == vis[v])
	{
		k = -1;
		while(k != v)
		{
			k = st[st_top];
			st_top--;
			in_st[k] = 0;
			printf("%d ", k);
		}
		printf("\n");
	}
}

int main()
{
	int i, j, a, b;

	while(scanf("%d %d", &n, &m) != EOF)
	{
		memset(mp, 0, sizeof(mp));
		for(i = 0; i < m; i++)
		{
			scanf("%d %d", &a, &b);
			mp[a][b] = 1;
		}

		memset(vis, -1, sizeof(vis));
		for(i = 1; i <= n; i++)
		{
			if(vis[i] == -1)
			{
				vis_t = 1;
				st_top = -1;
				memset(in_st, 0, sizeof(in_st));
				tarjan(i);
			}
		}
	}
	return 0;
}

/*

6 8
1 2
1 3
2 4
3 4
3 5
4 1
4 6
5 6

*/