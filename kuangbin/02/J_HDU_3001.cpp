/* http://acm.hdu.edu.cn/showproblem.php?pid=3001 */
/* 用dfs会TLE,这题貌似要用三进制状态压缩dp */
#include <stdio.h>
#include <string.h>

const int MAX_N = 12;

int n, m, ans;
int map[MAX_N][MAX_N];
int book[MAX_N];

void dfs(int v, int k, int val)
{
	int i;
	if(k == n)
	{
		if(ans == -1 || ans > val)
		{
			ans = val;
		}
		return ;
	}
	for(i = 1; i <= n; i++)
	{
		if(map[v][i] != -1 && book[i] < 2)
		{
			book[i] += 1;
			if(book[i] == 1)
			{
				dfs(i, k + 1, val + map[v][i]);
			}
			else if(book[i] == 2)
			{
				dfs(i, k, val + map[v][i]);
			}
			book[i] -= 1;
		}
	}
}

int main()
{
	int i, a, b, c;

	while(scanf("%d %d", &n, &m) != EOF)
	{
		memset(map, -1, sizeof(map));
		for(i = 0; i < m; i++)
		{
			scanf("%d %d %d", &a, &b, &c);
			if(map[a][b] == -1 || map[a][b] > c)
			{
				map[a][b] = c;
				map[b][a] = c;
			}
		}
		if(n == 0 || m == 0)
		{
			printf("0\n");
			continue;
		}

		ans = -1;
		memset(book, 0, sizeof(book));
		for(i = 1; i <= n; i++)
		{
			book[i] += 1;
			dfs(i, 1, 0);
			book[i] -= 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}