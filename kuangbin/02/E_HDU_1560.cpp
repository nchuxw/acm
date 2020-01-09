/* http://acm.hdu.edu.cn/showproblem.php?pid=1560 */
#include <stdio.h>
#include <string.h>

const int MAXN = 10;

int n, ans;
char str[MAXN][MAXN];
int slen[MAXN];

int dfs(int p[], int l, int lit)
{
	int i, j, res;
	int book[4] = {0, 0, 0, 0};
	int p_next[MAXN];
	
	if(l > lit)
	{
		return 0;
	}
	j = 1;
	for(i = 0; i < n; i++)
	{
		if(p[i] < slen[i])
		{
			book[str[i][p[i]] - 'A'] = 1;
			j = 0;
		}
	}
	if(j == 1)
	{
		return 1;
	}
	for(i = 0; i < 4; i++)
	{
		if(book[i] == 0)
		{
			continue;
		}
		memcpy(p_next, p, sizeof(p_next));
		for(j = 0; j < n; j++)
		{
			if(str[j][p[j]] - 'A' == i)
			{
				p_next[j]++;
			}
		}
		res = dfs(p_next, l + 1, lit);
		if(res == 1)
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	int t;
	int i, j, res;
	int p[MAXN];

	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		getchar();
		for(i = 0; i < n; i++)
		{
			fgets(str[i], MAXN, stdin);
			slen[i] = strlen(str[i]) - 1;
			for(j = 0; j < slen[i]; j++)
			{
				if(str[i][j] == 'G') str[i][j] = 'B';
				else if(str[i][j] == 'T') str[i][j] = 'D';
			}
		}
		for(ans = 0; ans < 1e9; ans++)
		{
			memset(p, 0, sizeof(p));
			if(dfs(p, 0, ans) == 1)
			{
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
