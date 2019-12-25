/* http://poj.org/problem?id=3984 */
/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 10;

typedef struct
{
	int x, y;
} node;


int mp[MAXN][MAXN];
node ans[MAXN * MAXN];
node que[MAXN * MAXN];
int pre[MAXN * MAXN];

int bfs(node start, node end)
{
	int front, back, len, flag, i;
	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	node tep;

	que[0] = start;
	pre[0] = -1;
	mp[start.x][start.y] == 2;
	front = 0;
	back = 1;
	flag = 0;
	while(front != back && flag == 0)
	{
		for(i = 0; i < 4; i++)
		{
			tep.x = que[front].x + dir[i][0];
			tep.y = que[front].y + dir[i][1];
			if(mp[tep.x][tep.y] == 0)
			{
				que[back] = tep;
				pre[back] = front;
				mp[tep.x][tep.y] = 2;
				if(tep.x == 5 && tep.y == 5)
				{
					flag = 1;
					break;
				}
				back++;
			}
		}
		front++;
	}
	if(flag == 0)
	{
		return -1;
	}
	else
	{
		len = 0;
		for(i = back; i != -1; i = pre[i])
		{
			ans[len] = que[i];
			len++;
		}
		return len;
	}
}

int main()
{
	int i, j, len;
	
	memset(mp, -1, sizeof(mp));
	for(i = 1; i <= 5; i++)
	{
		for(j = 1; j <= 5; j++)
		{
			scanf("%d", &mp[i][j]);
		}
	}
	len = bfs(node{1, 1}, node{5, 5});
	for(i = len - 1; i >= 0; i--)
	{
		printf("(%d, %d)\n", ans[i].x - 1, ans[i].y - 1);
	}
	return 0;
}