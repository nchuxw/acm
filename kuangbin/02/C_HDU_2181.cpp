/* http://acm.hdu.edu.cn/showproblem.php?pid=2181 */
/* AC */
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 20;
const int M = 3;

int num;
int mp[N + 2][3];
int path[N + 2];
int book[N + 2];

void dfs(int v, int k, int m)
{
	int i;
	if(v == m)
	{
		if(k == N)
		{
			num++;
			printf("%d:  %d", num, m);
			for(i = 0; i < k; i++)
			{
				printf(" %d", path[i]);
			}
			printf("\n");
		}
		if(k != 0)
		{
			return ;
		}
	}

	for(i = 0; i < M; i++)
	{
		if(book[mp[v][i]] == 0)
		{
			book[mp[v][i]] = 1;
			path[k] = mp[v][i];
			dfs(mp[v][i], k + 1, m);
			book[mp[v][i]] = 0;
		}
	}
}

int main()
{
	int i, j, m;
	
	for(i = 1; i <= N; i++)
	{
		for(j = 0; j < M; j++)
		{
			scanf("%d", &mp[i][j]);
		}
		sort(mp[i], mp[i] + M);
	}

	while(scanf("%d", &m) != EOF && m > 0)
	{
		num = 0;
		path[0] = m;
		memset(book, 0, sizeof(book));
		dfs(m, 0, m);
	}
	return 0;
}