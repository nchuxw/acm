/* 进不了OJ */
#include <stdio.h>
#include <string.h>

const int MAXN = 15;

typedef struct
{
	int x, y;
} point;

int n, m;
char mp[MAXN][MAXN];
char book[MAXN][MAXN];
point que[MAXN * MAXN];
int cost[MAXN * MAXN];

int bfs(point s1, point s2)
{
	int front = 0, back = 2;
	int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	point tep;
	int i, j, ans;

	que[0] = s1;
	que[1] = s2;
	cost[0] = 0;
	cost[1] = 0;
	memcpy(book, mp, sizeof(book));
	book[s1.x][s1.y] = '.';
	book[s2.x][s2.y] = '.';
	while(front != back)
	{
		for(i = 0; i < 4; i++)
		{
			tep = que[front];
			tep.x += dir[i][0];
			tep.y += dir[i][1];
			if(book[tep.x][tep.y] == '#')
			{
				que[back] = tep;
				cost[back] = cost[front] + 1;
				book[tep.x][tep.y] = '.';
				back++;
			}
		}
		front++;
	}
	ans = cost[back - 1];
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= m; j++)
		{
			if(book[i][j] == '#')
			{
				return -1;
			}
		}
	}
	return ans;
}

int main()
{
	int t, cas, ans;
	int i, res;
	point s1, s2;

	scanf("%d", &t);
	memset(mp, '.', sizeof(mp));
	for(cas = 1; cas <= t; cas++)
	{
		scanf("%d%d", &n, &m);
		getchar();
		for(i = 1; i <= n; i++)
		{
			fgets(mp[i] + 1, MAXN, stdin);
		}

		ans = 100000;
		for(s1.x = 1; s1.x <= n; s1.x++)
		{
			for(s1.y = 1; s1.y <= m; s1.y++)
			{
				if(mp[s1.x][s1.y] != '#')
				{
					continue;
				}
				for(s2.x = 1; s2.x <= n; s2.x++)
				{
					for(s2.y = 1; s2.y <= m; s2.y++)
					{
						if(mp[s2.x][s2.y] != '#')
						{
							continue;
						}
						res = bfs(s1, s2);
						if(res != -1 && res < ans)
						{
							ans = res;
						}
					}
				}
			}
		}
		printf("Case %d: ", cas);
		if(ans == 100000)
		{
			printf("-1\n");
		}
		else
		{
			printf("%d\n", ans);
		}
	}
	return 0;
}