/* http://acm.hdu.edu.cn/showproblem.php?pid=1560 */
/* AC */
#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int MAXN = 10;

int n, ans;
char str[MAXN][MAXN];
char sp[5] = {"ACGT"};
int slen[MAXN];

int dfs(int p[], int l, int lit)
{
	int i, j, flag, res;
	int p_next[MAXN];
	
	if(l > lit)
	{
		return 0;
	}
	flag = 0;
	for(i = 0; i < n; i++)
	{
		if(flag < slen[i] - p[i])
		{
			flag = slen[i] - p[i];
		}
	}
	if(flag > lit - l)
	{
		return 0;
	}
	if(flag == 0)
	{
		return 1;
	}
	for(i = 0; i < 4; i++)
	{
		memcpy(p_next, p, n * sizeof(int));
		flag = 0;
		for(j = 0; j < n; j++)
		{
			if(str[j][p_next[j]] == sp[i])
			{
				p_next[j]++;
				flag = 1;
			}
		}
		if(flag == 1)
		{
			res = dfs(p_next, l + 1, lit);
			if(res == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

// typedef struct node
// {
// 	int p;
// 	int len;
// } node;

// int bfs()
// {
// 	int i, j, flag;
// 	int book[4], p[MAXN], p_next[MAXN];
// 	node tep;
// 	queue<node> que;

// 	que.push((node){0, 0});
// 	while(que.empty() == false)
// 	{
// 		memset(book, 0, sizeof(book));
// 		tep = que.front();
// 		j = 1;
// 		for(i = 0; i < n; i++)
// 		{
// 			p[n - i - 1] = (tep.p / j) % 10;
// 			j *= 10;
// 		}
// 		for(i = 0; i < n; i++)
// 		{
// 			if(p[i] < slen[i])
// 			{
// 				book[str[i][p[i]] - 'A'] = 1;
// 			}
// 		}
// 		tep.len++;
// 		for(i = 0; i < 4; i++)
// 		{
// 			if(book[i] == 0)
// 			{
// 				continue;
// 			}
// 			memcpy(p_next, p, n * sizeof(int));
// 			flag = 1;
// 			for(j = 0; j < n; j++)
// 			{
// 				if(str[j][p_next[j]] - 'A' == i)
// 				{
// 					p_next[j]++;
// 				}
// 				if(p_next[j] < slen[j])
// 				{
// 					flag = 0;
// 				}
// 			}
// 			if(flag == 0)
// 			{
// 				tep.p = 0;
// 				for(i = 0; i < n; i++)
// 				{
// 					tep.p = tep.p * 10 + p_next[i];
// 				}
// 				que.push(tep);
// 			}
// 			else
// 			{
// 				return tep.len;
// 			}
// 		}
// 		que.pop();
// 	}
// }

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
		}

		for(ans = 0; ans < 1e9; ans++)
		{
		    memset(p, 0, sizeof(p));
		    if(dfs(p, 0, ans) == 1)
		    {
		        break;
		    }
		}

		// ans = 0;
		// for(i = 0; i < n; i++)
		// {
		// 	if(slen[i] != 0)
		// 	{
		// 		ans = 1;
		// 		break;
		// 	}
		// }
		// if(ans == 1)
		// {
		// 	ans = bfs();
		// }
		printf("%d\n", ans);
	}
	return 0;
}