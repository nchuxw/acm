/* https://cn.vjudge.net/contest/67418#problem/B */
/* runtime error */
#include <stdio.h>
#include <string.h>
#define min(a, b) (a < b) ? a : b

const int MAX_N = 100 + 10;

int n;
int mp[MAX_N][MAX_N];
int vis[MAX_N], vis_n;
int low[MAX_N];
int is_ctp[MAX_N];

int tarjan(int v, int root)
{
	int i, child = 0;

	vis[v] = vis_n;
	low[v] = vis_n;
	vis_n++;
	for(i = 1; i <= n; i++)
	{
		if(mp[v][i] != 0)
		{
			if(vis[i] == -1)
			{
				tarjan(i, root);
				low[v] = min(low[v], low[i]);
				if(v == root)
				{
					child++;
				}
				else if(low[i] >= vis[v])
				{
					is_ctp[v] = 1;
				}
			}
			else
			{
				low[v] = min(low[v], vis[i]);
			}
		}
	}
	if(v == root && child >= 2)
	{
		is_ctp[root] = true;
	}
}

int main()
{
	int i, a, b, ans;
	char ch;

	while(scanf("%d", &n) != EOF && n != 0)
	{
		memset(mp, 0, sizeof(mp));
		while(scanf("%d", &a) != EOF && a != 0)
		{
			while(scanf("%d", &b) != EOF)
			{
				mp[a][b] = 1;
				mp[b][a] = 1;
				ch = getchar();
				if(ch == '\n')
				{
					break;
				}
			}
		}

		memset(vis, -1, sizeof(vis));
		memset(is_ctp, 0, sizeof(is_ctp));
		for(i = 1; i <= n; i++)
		{
			if(vis[i] == -1)
			{
				vis_n = 1;
				tarjan(i, i);
			}
		}
		ans = 0;
		for(i = 1; i <= n; i++)
		{
			if(is_ctp[i] == 1)
			{
				ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

/*

5
5 1 2 3 4
0
6
2 1 3
5 4 6 2
0
0


1
2

*/