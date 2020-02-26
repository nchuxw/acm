/* http://acm.hdu.edu.cn/showproblem.php?pid=2102 */
/* AC */
#include <stdio.h>
#include <string.h>

const int MAX_N = 12;

typedef struct node
{
	int x, y, z;
	int t;
} node;

int n, m, t;
char map[2][MAX_N][MAX_N];

int solve()
{
	int i, j, front, back;
	int book[2][MAX_N][MAX_N];
	node que[2 * MAX_N * MAX_N];
	node tep;
	int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

	que[0] = (node){0, 0, 0, 0};
	front = 0;
	back = 1;
	memset(book, 0, sizeof(book));
	book[0][0][0] = 1;
	while(front != back)
	{
		for(i = 0; i < 4; i++)
		{
			tep = que[front];
			tep.x += dir[i][0];
			tep.y += dir[i][1];
			tep.t++;
			if(tep.x < 0 || tep.x >= n || tep.y < 0 || tep.y >= m || tep.t > t)
			{
				continue;
			}
			if(map[tep.z][tep.x][tep.y] == '#')
			{
				tep.z = !tep.z;
			}
			if(map[tep.z][tep.x][tep.y] == '*' || map[tep.z][tep.x][tep.y] == '#' || book[tep.z][tep.x][tep.y] == 1)
			{
				continue;
			}
			if(map[tep.z][tep.x][tep.y] == 'P')
			{
				return tep.t;
			}
			book[tep.z][tep.x][tep.y] = 1;
			que[back] = tep;
			back++;
		}
		front++;
	}
	return 0;
}

int main()
{
	int c, i, ans;

	scanf("%d", &c);
	while(c--)
	{
		scanf("%d %d %d", &n, &m, &t);
		getchar();
		for(i = 0; i < n; i++)
		{
			scanf("%s", map[0][i]);
		}
		getchar();
		for(i = 0; i < n; i++)
		{
			scanf("%s", map[1][i]);
		}

		ans = solve();
		if(ans == 0)
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
	}
	return 0;
}
