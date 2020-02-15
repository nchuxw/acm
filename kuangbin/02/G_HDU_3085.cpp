/* http://acm.hdu.edu.cn/showproblem.php?pid=3085 */
/* AC */
#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int MAX_N = 800 + 10;
// const int MAX_N = 2 + 10;

typedef struct point
{
	int x, y;
} point;

int n, m;
char mp[MAX_N][MAX_N];
char book[2][MAX_N][MAX_N];
queue<point> que[2];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int abs(int a, int b)
{
	return (a > b) ? a - b : b - a;
}

int check_point(point p, point zs[], int t)
{
	if (abs(p.x, zs[0].x) + abs(p.y, zs[0].y) <= 2 * t || 
		abs(p.x, zs[1].x) + abs(p.y, zs[1].y) <= 2 * t)
	{
		return 1;
	}
	return 0;
}

int step_one(int mg, point zs[], int t)
{
	int i, pn;
	point front, tep;

	pn = que[mg].size();
	while(pn--)
	{
		front = que[mg].front();
		que[mg].pop();
		if(check_point(front, zs, t))
		{
			continue;
		}
		for(i = 0; i < 4; i++)
		{
			tep = front;
			tep.x += dir[i][0];
			tep.y += dir[i][1];
			if(tep.x < 0 || tep.x >= n || tep.y < 0 || tep.y >= m)
			{
				continue;
			}
			if(check_point(tep, zs, t) || mp[tep.x][tep.y] == 'X' || book[mg][tep.x][tep.y] == 1)
			{
				continue;
			}
			if(book[!mg][tep.x][tep.y] == 1)
			{
				return 1;
			}
			book[mg][tep.x][tep.y] = 1;
			que[mg].push(tep);
		}
	}
	return 0;
}

int solve(point ms, point gs, point zs[])
{
	int t;

	memset(book, 0, sizeof(book));
	book[0][ms.x][ms.y] = 1;
	book[1][gs.x][gs.y] = 1;
	que[0].push(ms);
	que[1].push(gs);
	t = 0;
	while(que[0].empty() == false || que[1].empty() == false)
	{
		t++;
		if(step_one(0, zs, t) == 1) return t;
		if(step_one(0, zs, t) == 1) return t;
		if(step_one(0, zs, t) == 1) return t;
		if(step_one(1, zs, t) == 1) return t;
	}
	return -1;
}

int main()
{
	int t, i, j, k, ans;
	point ms, gs, zs[2];

	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d", &n, &m);
		getchar();
		k = 0;
		for(i = 0; i < n; i++)
		{
			scanf("%s", mp[i]);
			for(j = 0; j < m; j++)
			{
				if(mp[i][j] == 'M')
				{
					ms = (point){i, j};
				}
				else if(mp[i][j] == 'G')
				{
					gs = (point){i, j};
				}
				else if(mp[i][j] == 'Z')
				{
					zs[k] = (point){i, j};
					k++;
				}
			}
		}

		while(que[0].empty() == false) que[0].pop();
		while(que[1].empty() == false) que[1].pop();		
		ans = solve(ms, gs, zs);
		printf("%d\n", ans);
	}
	return 0;
}