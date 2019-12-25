/* http://acm.hdu.edu.cn/showproblem.php?pid=1241 */
/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 100 + 10;

int n, m;
char mp[MAXN][MAXN];
int dir[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

void dfs(int x, int y)
{
	int i, xt, yt;
	mp[x][y] = '*';
	for(i = 0; i < 8; i++)
	{
		xt = x + dir[i][0];
		yt = y + dir[i][1];
		if(mp[xt][yt] == '@')
		{
			dfs(xt, yt);
		}
	}
}

int main()
{
	int i, j, ans;

	while(scanf("%d%d", &n, &m) != EOF)
	{
		if(n == 0)
		{
			break;
		}
		getchar();
		memset(mp, '*', sizeof(mp));
		for(i = 1; i <= n; i++)
		{
			// scanf("%s", mp[i] + 1);
			fgets(mp[i] + 1, MAXN - 1, stdin);
		}
		
		ans = 0;
		for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= m; j++)
			{
				if(mp[i][j] == '@')
				{
					ans++;
					dfs(i, j);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}