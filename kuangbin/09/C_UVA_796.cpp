/* https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=737 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define min(a, b) (a < b) ? a : b

const int MAX_N = 1000 + 10;
// const int MAX_N = 10;

typedef struct node
{
	int b;
	int next;
} node;

typedef struct edge
{
	int a, b;
} edge;

int cmp(edge a, edge b)
{
	if(a.a != b.a)
	{
		return a.a < b.a;
	}
	else
	{
		return a.b < b.b;
	}
}

int n, bn;
node e[2 * MAX_N * MAX_N];
edge bridge[MAX_N];
int head[MAX_N];
int vis[MAX_N], v_ind;
int low[MAX_N];

void tarjan(int v, int pre)
{
	int i, b;

	vis[v] = v_ind;
	low[v] = v_ind;
	v_ind++;
	for(i = head[v]; i != -1; i = e[i].next)
	{
		b = e[i].b;
		if(vis[b] == 0)
		{
			tarjan(b, v);
			low[v] = min(low[v], low[b]);
			if(low[b] > vis[v])
			{
				if(v < b)
				{
					bridge[bn].a = v;
					bridge[bn].b = b;
				}
				else
				{
					bridge[bn].a = b;
					bridge[bn].b = v;
				}
				bn++;
			}
		}
		else if(b != pre)
		{
			low[v] = min(low[v], vis[b]);
		}
	}
}

int main()
{
	int a, k, b;
	int i, j, en;

	while(scanf("%d", &n) != EOF)
	{
		memset(head, -1, sizeof(head));
		en = 0;
		for(i = 0; i < n; i++)
		{
			scanf("%d (%d)", &a, &k);
			for(j = 0; j < k; j++)
			{
				scanf("%d", &b);
				e[en].b = b;
				e[en].next = head[a];
				head[a] = en;
				en++;
			}
		}
		// for(i = 0; i < n; i++)
		// {
		// 	for(j = head[i]; j != -1; j = e[j].next)
		// 	{
		// 		printf("%d ", e[j].b);
		// 	}
		// 	printf("\n");
		// }

		bn = 0;
		v_ind = 1;
		memset(vis, 0, sizeof(vis));
		for(i = 0; i < n; i++)
		{
			if(vis[i] == 0)
			{
				tarjan(i, i);
			}
		}
		
		std::sort(bridge, bridge + bn, cmp);
		printf("%d critical links\n", bn);
		for(i = 0; i < bn; i++)
		{
			printf("%d - %d\n", bridge[i].a, bridge[i].b);
		}
		printf("\n");
	}
	return 0;
}

/*

8
0 (1) 1
1 (3) 2 0 3
2 (2) 1 3
3 (3) 1 2 4
4 (1) 3
7 (1) 6
6 (1) 7
5 (0)

0


3 critical links
0 - 1
3 - 4
6 - 7

0 critical links

*/