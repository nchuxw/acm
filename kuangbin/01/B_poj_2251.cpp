/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 30 + 5;

typedef struct node
{
	int x, y, z;
} node;

int bfs(char mp[][MAXN][MAXN], int size[], node start, char end_char)
{
	int front, back;
	node que[30000];
	int cost[30000];
	node dir[6] = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};
	int i, x, y, z, ans = -1;

	memcpy(que, &start, sizeof(start));
	cost[0] = 0;
	front = 0;
	back = 1;
	while(front != back && ans == -1)
	{
		for(i = 0; i < 6; i++)
		{
			x = que[front].x + dir[i].x;
			y = que[front].y + dir[i].y;
			z = que[front].z + dir[i].z;
			if(mp[x][y][z] == '.')
			{
				que[back] = (node){x, y, z};
				cost[back] = cost[front] + 1;
				back++;
				mp[x][y][z] = '*';
			}
			if(mp[x][y][z] == end_char)
			{
				ans = cost[front] + 1;
				break;
			}
		}
		front++;
	}
	return ans;
}

int main()
{
	int size[3];
	int i, j, k, ans;
	char mp[MAXN][MAXN][MAXN];
	node start;
	
	while(scanf("%d%d%d", &size[0], &size[1], &size[2]) != EOF)
	{
		getchar();
		if(size[0] == 0 && size[1] == 0 && size[2] == 0)
		{
			break;
		}
		memset(mp, '#', sizeof(mp));
		for(i = 1; i <= size[0]; i++)
		{
			for(j = 1; j <= size[1]; j++)
			{
				fgets(mp[i][j] + 1, MAXN, stdin);
				for(k = 1; k <= size[2]; k++)
				{
					if(mp[i][j][k] == 'S')
					{
						start = (node){i, j, k};
					}
				}
			}
			getchar();
		}

		ans = bfs(mp, size, start, 'E');
		if(ans == -1)
		{
			printf("Trapped!\n");
		}
		else
		{
			printf("Escaped in %d minute(s).\n", ans);
		}
	}
	return 0;
}