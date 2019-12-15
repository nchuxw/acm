/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 20;

int n, m;
int mp[MAXN][MAXN];

int solve(int tep[][MAXN]);

int main()
{
	int i, j, num, min;
	int tep[MAXN][MAXN], ans[MAXN][MAXN];

	while(scanf("%d%d", &n, &m) != EOF)
	{
		for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= m; j++)
			{
				scanf("%d", &mp[i][j]);
			}
		}
		min = MAXN * MAXN;
		for(i = 0; i < (1 << m); i++)
		{
			memset(tep, 0, sizeof(tep));
			for(j = 1; j <= m; j++)
			{
				tep[0][j] = (i >> (j - 1)) & 1;
			}
			// for(j = 1; j <= n; j++)
			// {
			// 	printf("%d ", tep[1][j]);
			// }
			// printf("\n");
			num = solve(tep);
			if(num != -1 && num < min)
			{
				min = num;
				memcpy(ans, tep, sizeof(ans));
			}
		}
		if(min == MAXN * MAXN)
		{
			printf("IMPOSSIBLE\n");
		}
		else
		{
			for(i = 1; i <= n; i++)
			{
				for(j = 1; j < m; j++)
				{
					printf("%d ", ans[i][j]);
				}
				printf("%d\n", ans[i][m]);
			}
		}
	}
	return 0;
}

int solve(int tep[][MAXN])
{
	int i, j, k, x, y, num;
	int dir[5][2] = {{0, 0}, {0, 1}, {1, 0}, {-1, 0}, {0, -1}};
	int stat[MAXN][MAXN];

	num = 0;
	memcpy(stat, mp, sizeof(stat));
	memcpy(stat[0], tep[0], sizeof(stat[0]));
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= m; j++)
		{
			if(stat[i - 1][j] != 0)
			{
				for(k = 0; k < 5; k++)
				{
					x = i + dir[k][0];
					y = j + dir[k][1];
					stat[x][y] = !stat[x][y];
				}
				tep[i][j] = 1;
				num ++;
			}
		}
	}
	for(i = 1; i <= m; i++)
	{
		if(stat[n][i] != 0)
		{
			num = -1;
			break;
		}
	}
	return num;
}