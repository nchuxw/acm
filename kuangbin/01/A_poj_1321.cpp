/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 10;

char mp[MAXN][MAXN];
int col_book[MAXN];

int dfs(int i, int n, int k)
{
	int j, ans;
	if(k == 0)
	{
		return 1;
	}
	ans = 0;
	for(j = 0; j < n; j++)
	{
		if(mp[i][j] == '#' && col_book[j] == 0)
		{
			col_book[j] = 1;
			ans += dfs(i + 1, n, k - 1);
			col_book[j] = 0;
		}
	}
	if(n - i >= k)
	{
		ans += dfs(i + 1, n, k);
	}
	return ans;
}

int main()
{
	int n, k;
	int i, ans;

	while(scanf("%d%d", &n, &k) != EOF)
	{
		getchar();
		if(n == -1 && k == -1)
		{
			break;
		}
		// if(k == 0)
		// {
		// 	printf("1\n");
		// 	continue;
		// }
		memset(mp, '.', sizeof(mp));
		memset(col_book, 0, sizeof(col_book));
		for(i = 1; i <= n; i++)
		{
			fgets(mp[i], MAXN, stdin);
		}
		ans = 0;
		ans += dfs(1, n, k);
		printf("%d\n", ans);
	}
	return 0;
}