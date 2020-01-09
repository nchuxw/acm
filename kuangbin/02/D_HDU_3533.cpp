/* http://acm.hdu.edu.cn/showproblem.php?pid=3533 */
/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 100 + 10;
const int MAXT = 1000 + 10;

typedef struct fort_t
{
	int d, x, y, t, v;
} fort_t;

typedef struct node
{
	int x, y, t;
} node;

int n, m, k, d;
char book[MAXN][MAXN][MAXT];
fort_t fort[MAXN];
node que[MAXN * MAXN * MAXT];
int dir[5][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {0, 0}};

void init()
{
	int i, j, s;
	char isf[MAXN][MAXN];
	fort_t ft;

	memset(book, 0, sizeof(book));
	memset(isf, 0, sizeof(isf));
	for(i = 0; i < k; i++)
	{
		ft = fort[i];
		memset(book[ft.x][ft.y], 1, sizeof(book[ft.x][ft.y]));
		isf[ft.x][ft.y] = 1;
	}
	for(i = 0; i < k; i++)
	{
		ft = fort[i];
		for(j = 1; j < MAXN; j++)
		{
			ft.x += dir[ft.d][0];
			ft.y += dir[ft.d][1];
			if(ft.x < 0 || ft.y < 0 || ft.x > n || ft.y > m || isf[ft.x][ft.y] != 0)
			{
				break;
			}
			if(j % ft.v == 0)
			{
				for(s = j / ft.v; s < MAXT; s += ft.t)
				{
					book[ft.x][ft.y][s] = 1;
				}
			}
		}
	}
}

int bfs(node start, node end)
{
	int i, j;
	int front, back;
	node tep;

	que[0] = start;
	front = 0;
	back = 1;
	while(front != back)
	{
		tep.t = que[front].t + 1;
		if(tep.t > d)
		{
			break;
		}
		for(i = 0; i < 5; i++)
		{
			tep.x = que[front].x + dir[i][0];
			tep.y = que[front].y + dir[i][1];
			if(tep.x < 0 || tep.y < 0 || tep.x > n || tep.y > m || book[tep.x][tep.y][tep.t] != 0)
			{
				continue;
			}
			book[tep.x][tep.y][tep.t] = 1;
			que[back] = tep;
			if(tep.x == end.x && tep.y == end.y)
			{
				return tep.t;
			}
			back++;
		}
		front++;
	}
	return -1;
}

int main()
{
	int i, j, ans;
	char c;

	while(scanf("%d%d%d%d", &n, &m, &k, &d) != EOF)
	{
		for(i = 0; i < k; i++)
		{
			getchar();
			scanf("%c%d%d%d%d", &c, &fort[i].t, &fort[i].v, &fort[i].x, &fort[i].y);
			if(c == 'N') fort[i].d = 0;
			if(c == 'S') fort[i].d = 1;
			if(c == 'E') fort[i].d = 2;
			if(c == 'W') fort[i].d = 3;
		}
		init();
		ans = bfs((node){0, 0, 0}, (node){n, m, 0});
		if(ans == -1)
		{
			printf("Bad luck!\n");
		}
		else
		{
			printf("%d\n", ans);
		}
	}
	return 0;
}