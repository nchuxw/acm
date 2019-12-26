/* http://acm.hdu.edu.cn/showproblem.php?pid=2612 */
/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 200 + 10;

typedef struct node
{
	int x, y;
	int cost;
} node;


int n, m;
char mp[MAXN][MAXN];
node que[MAXN * MAXN];
int cost[MAXN][MAXN];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void bfs(node start)
{
	int i, x, y;
	int front, back;
	int book[MAXN][MAXN];

	memset(book, 0, sizeof(book));
	que[0] = start;
	book[start.x][start.y] = 1;
	front = 0;
	back = 1;
	while(front != back)
	{
		for(i = 0; i < 4; i++)
		{
			x = que[front].x + dir[i][0];
			y = que[front].y + dir[i][1];
			if(mp[x][y] != '#' && book[x][y] == 0)
			{
				book[x][y] = 1;
				que[back] = (node){x, y, que[front].cost + 1};
				cost[x][y] += que[back].cost;
				back++;
			}
		}
		front++;
	}
}

int main()
{
	int i, j, ans;
	
	while(scanf("%d %d", &n, &m) != EOF)
	{
		getchar();
		memset(mp, '#', sizeof(mp));
		memset(cost, 0, sizeof(cost));
		for(i = 1; i <= n; i++)
		{
			fgets(mp[i] + 1, MAXN - 1, stdin);
		}
		for(i = 0; i <= n; i++)
		{
			mp[i][m + 1] = '#';
		}
		for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= m; j++)
			{
				if(mp[i][j] == 'Y' || mp[i][j] =='M')
				{
					bfs((node){i, j, 0});
				}
			}
		}
		ans = MAXN * MAXN;
		for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= m; j++)
			{
				if(mp[i][j] == '@' && cost[i][j] != 0 && cost[i][j] < ans)//cost[i][j] == 0代表i,j这个点无法到达
				{
					ans = cost[i][j];
				}
			}
		}
		printf("%d\n", ans * 11);
	}
	return 0;
}