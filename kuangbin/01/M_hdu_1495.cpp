/* http://acm.hdu.edu.cn/showproblem.php?pid=1495 */
/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 100 + 10;

typedef struct
{
	int st[3];
	int cost;
} stat;

int book[MAXN][MAXN];
stat que[MAXN * MAXN];
int dir[6][2] = {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}};

int bfs(int lim[])
{
	int i, a, b;
	int front, back;
	stat tep;

	memset(book, 0, sizeof(book));
	que[0] = (stat){{lim[0], 0, 0}, 0};
	book[lim[0]][0] = 1;
	front = 0;
	back = 1;
	while(front != back)
	{
		for(i = 0; i < 6; i++)
		{
			tep = que[front];
			tep.cost++;
			a = dir[i][0];
			b = dir[i][1];
			if(tep.st[a] + tep.st[b] < lim[b])
			{
				tep.st[b] += tep.st[a];
				tep.st[a] = 0;
			}
			else
			{
				tep.st[a] -= (lim[b] - tep.st[b]);
				tep.st[b] = lim[b];
			}
			if(book[tep.st[0]][tep.st[1]] == 0)
			{
				if( (tep.st[0] == tep.st[1] && tep.st[2] == 0) ||
					(tep.st[0] == tep.st[2] && tep.st[1] == 0) ||
					(tep.st[1] == tep.st[2] && tep.st[0] == 0))
				{
					return tep.cost;
				}
				que[back] = tep;
				book[tep.st[0]][tep.st[1]] = 1;
				back++;
			}
		}
		front++;
	}
	return -1;
}

int main()
{
	int lim[3];
	int ans;

	while(scanf("%d%d%d", &lim[0], &lim[1], &lim[2]) != EOF)
	{
		if(lim[0] == 0 && lim[1] == 0 && lim[2] == 0)
		{
			break;
		}
		ans = bfs(lim);
		if(ans < 0)
		{
			printf("NO\n");
		}
		else
		{
			printf("%d\n", ans);
		}
	}
	return 0;
}