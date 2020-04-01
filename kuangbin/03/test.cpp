#include <stdio.h>
#include <string.h>

const int MAX_N = 1000 + 10;

int a[MAX_N], n, ans;
int book[MAX_N];
int mp[MAX_N][MAX_N];

void dfs(int v, int d, int k)
{
	int i;

	for(i = 1; i <= mp[v][0]; i++)
	{
		if(book[mp[v][i]] == 0)
		{
			k++;
		}
		book[mp[v][i]]++;
	}
	if(k == n)
	{
		if(d > ans)
		{
			ans = d;
		}
	}
	else
	{
		for(i = 0; i < n; i++)
		{
			if(book[i] == 0)
			{
				dfs(i, d + 1, k);
			}
		}
	}
	for(i = 1; i <= mp[v][0]; i++)
	{
		book[mp[v][i]]--;
	}
}

int main()
{
	int t;
	int i, j, res;

	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);
		}

		for(i = 0; i < n; i++)
		{
			mp[i][0] = 0;
			for(j = 0; j < n; j++)
			{
				if(a[i] % a[j] == 0 || a[j] % a[i] == 0)
				{
					mp[i][0]++;
					mp[i][mp[i][0]] = j;
				}
			}
		}
		memset(book, 0, sizeof(book));
		ans = 0;
		for(i = 0; i < n; i++)
		{
			dfs(i, 1, 0);
		}
		printf("%d\n", ans);
	}
	return 0;
}