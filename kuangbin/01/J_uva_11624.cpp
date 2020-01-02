/* https://vjudge.net/problem/UVA-11624 */
/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 1000 + 10;

typedef struct 
{
	int x, y;
} node;

char mp[MAXN][MAXN];
node que[MAXN * MAXN];
int fct[MAXN][MAXN];
int jct[MAXN][MAXN];
int book[MAXN][MAXN];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void bfs(int sn, int cost[][MAXN])
{
	int i, c;
	int front = 0, back = sn;
	node tep;

	while(front != back)
	{
		c = cost[que[front].x][que[front].y] + 1;
		for(i = 0; i < 4; i++)
		{
			tep = que[front];
			tep.x += dir[i][0];
			tep.y += dir[i][1];
			if(mp[tep.x][tep.y] != '#' && book[tep.x][tep.y] == 0)
			{
				que[back] = tep;
				cost[tep.x][tep.y] = c;
				book[tep.x][tep.y] = 1;
				back++;
			}
		}
		front++;
	}
}

int main()
{
	int t, n, m;
	int i, j, sn, ans;
	node tep[1];

	scanf("%d", &t);
	memset(mp, '#', sizeof(mp));
	while(t--)
	{
		scanf("%d%d", &n, &m);
		getchar();
		for(i = 1; i <= n; i++)
		{
			fgets(mp[i] + 1, MAXN, stdin);
			mp[i][m + 1] = '#';
		}
		for(i = 1; i <= m + 1; i++)
		{
			mp[n + 1][i] = '#';
		}
		
		sn = 0;
		memset(jct, 0x2f, sizeof(jct));
		memset(book, 0, sizeof(book));
		for(i = 1; i <= n && sn == 0; i++)
		{
			for(j = 1; j <= m; j++)
			{
				if(mp[i][j] == 'J')
				{
					que[sn] = (node){i, j};
					jct[i][j] = 0;
					book[i][j] = 1;
					sn++;
					break;
				}
			}
		}
		bfs(1, jct);
		// for(i = 0; i <= n + 1; i++)
		// {
		// 	for(j = 0; j <= m + 1; j++)
		// 	{
		// 		printf("%d ", jct[i][j]);
		// 	}
		// 	printf("\n");
		// }

		sn = 0;
		memset(fct, 0x2f, sizeof(fct));
		memset(book, 0, sizeof(book));
		for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= m; j++)
			{
				if(mp[i][j] == 'F')
				{
					que[sn] = (node){i, j};
					fct[i][j] = 0;
					book[i][j] = 1;
					sn++;
				}
			}
		}
		bfs(sn, fct);
		// for(i = 0; i <= n + 1; i++)
		// {
		// 	for(j = 0; j <= m + 1; j++)
		// 	{
		// 		printf("%d ", fct[i][j]);
		// 	}
		// 	printf("\n");
		// }

		ans = MAXN * MAXN;
		for(i = 1; i <= n; i++)
		{
			if(jct[i][1] < fct[i][1] && ans > jct[i][1])
			{
				ans = jct[i][1];
			}
			if(jct[i][m] < fct[i][m] && ans > jct[i][m])
			{
				ans = jct[i][m];
			}
		}
		for(i = 1; i <= m; i++)
		{
			if(jct[1][i] < fct[1][i] && ans > jct[1][i])
			{
				ans = jct[1][i];
			}
			if(jct[n][i] < fct[n][i] && ans > jct[n][i])
			{
				ans = jct[n][i];
			}
		}
		if(ans == MAXN * MAXN)
		{
			printf("IMPOSSIBLE\n");
		}
		else
		{
			printf("%d\n", ans + 1);
		}
	}
	return 0;
}