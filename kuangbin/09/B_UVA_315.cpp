/* vis_tarjan算法求强连通分量的个数 */
#include <stdio.h>
#include <string.h>
#define min(a, b) (a < b) ? a : b

const int MAX_N = 100 + 10;

int n;
int mp[MAX_N][MAX_N];
int vis[MAX_N], vis_t;
int low[MAX_N];
int is_ctp[MAX_N];

int tarjan(int v, int father)
{
	int i;

	vis[v] = vis_t;
	low[v] = vis_t;
	vis_t++;
	for(i = 1; i <= n; i++)
	{
		if(mp[v][i] == 0)
		{
			continue;
		}
		if(vis[i] == -1)
		{
			tarjan(i, v);
			low[v] = min(low[v], low[i]);
		}
		else if(i != father)
		{
			low[v] = min(low[v], vis[i]);
		}
	}
	if(low[v] == vis[v])
	{
	}
}

int main()
{
	int i, j, a, b;
	char ch;

	while(scanf("%d", &n) != EOF && n != 0)
	{
		while(scanf("%d", &a) != EOF && a != 0)
		{
			while(scanf("%d %c", &b, &ch) != EOF)
			{
				mp[a][b] = 1;
				mp[b][a] = 1;
				if(ch == '\n')
				{
					break;
				}
			}
		}
		
	}
	return 0;
}