/* http://acm.hdu.edu.cn/showproblem.php?pid=3533 */
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
	int x, y, t, d;
} node;

int n, m, k, d;
char book[MAXN][MAXN][MAXT];
fort_t fort[MAXN];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void init()
{
	int i, j, k;
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
		for(j = 0; j < )
	}
}

int main()
{
	int i, j;
	char c;

	while(scanf("%d%d%d%d", &n, &m, &k, &d) != EOF)
	{
		getchar();
		for(i = 0; i < k; i++)
		{
			scanf("%c%d%d%d%d", &c, &fort[i].t, &fort[i].v, &fort[i].x, &fort[i].y);
			if(c == 'N') fort[i].d = 0;
			if(c == 'S') fort[i].d = 1;
			if(c == 'E') fort[i].d = 2;
			if(c == 'W') fort[i].d = 3;
		}
		init();
	}
	return 0;
}