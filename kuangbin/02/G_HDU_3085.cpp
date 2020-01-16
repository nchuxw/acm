/* http://acm.hdu.edu.cn/showproblem.php?pid=3085 */
#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int MAX_N = 800 + 10;
// const int MAX_N = 2 + 10;

typedef struct point
{
	int x, y, t;
} point;

char mp[MAX_N][MAX_N];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir2[12][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 2}, {0, -2}, {2, 0}, {-2, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
// int dir3[24][2] = 
// {
// 	{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 2}, {0, -2}, {-2, 0}, {2, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
// 	{0, 3}, {0, -3}, {3, 0}, {-3, 0}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}
// };

int bfs(int n, int m, point ms, point gs, point zs[])
{
	int t, x, y, i;
	point tep;
	queue<point> mq;
	queue<point> gq;
	queue<point> zq;
	queue<point> que;

	mq.push(ms);
	gq.push(gs);
	zq.push(zs[0]);
	zq.push(zs[1]);
	while(mq.empty() == false && gq.empty() == false)
	{
		t = 1e9;
		if(zq.empty() == false && t > zq.front().t)
		{
			t = zq.front().t;
		}
		if(t > mq.front().t)
		{
			t = mq.front().t;
		}
		if(t > gq.front().t)
		{
			t = gq.front().t;
		}

		while(zq.empty() == false && zq.front().t == t)
		{
			tep = zq.front();
			zq.pop();
			for(i = 0; i < 12; i++)
			{
				x = tep.x + dir2[i][0];
				y = tep.y + dir2[i][1];
				if(x < 0 || n <= x || y < 0 || m <= y || mp[x][y] == 'Z' || mp[x][y] == 'X')
				{
					continue;
				}
				mp[x][y] = 'Z';
				zq.push((point){x, y, t + 1});
			}
		}

		while(mq.empty() == false && mq.front().t == t)
		{
			tep = mq.front();
			mq.pop();
			if(mp[tep.x][tep.y] != 'M')
			{
				continue;
			}
			tep.t = 0;
			que.push(tep);
		}
		while(que.empty() == false)
		{
			tep = que.front();
			que.pop();
			tep.t++;
			if(tep.t > 3)
			{
				continue;
			}
			for(i = 0; i < 4; i++)
			{
				x = tep.x + dir[i][0];
				y = tep.y + dir[i][1];
				if(mp[x][y] == 'G')
				{
					return t + 1;
				}
				if(x < 0 || n <= x || y < 0 || m <= y || mp[x][y] != '.')
				{
					continue;
				}
				mp[x][y] = 'M';
				que.push((point){x, y, tep.t});
				mq.push((point){x, y, t + 1});
			}
		}

		while(gq.empty() == false && gq.front().t == t)
		{
			tep = gq.front();
			gq.pop();
			if(mp[tep.x][tep.y] != 'G')
			{
				continue;
			}
			tep.t = 0;
			que.push(tep);
		}
		while(que.empty() == false)
		{
			tep = que.front();
			que.pop();
			tep.t++;
			if(tep.t > 1)
			{
				continue;
			}
			for(i = 0; i < 4; i++)
			{
				x = tep.x + dir[i][0];
				y = tep.y + dir[i][1];
				if(mp[x][y] == 'M')
				{
					return t + 1;
				}
				if(x < 0 || n <= x || y < 0 || m <= y || mp[x][y] != '.')
				{
					continue;
				}
				mp[x][y] = 'G';
				que.push((point){x, y, tep.t});
				gq.push((point){x, y, t + 1});
			}
		}
	}
	return -1;
}

int main()
{
	int t, n, m;
	int i, j, k, ans;
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
					ms = (point){i, j, 0};
				}
				else if(mp[i][j] == 'G')
				{
					gs = (point){i, j, 0};
				}
				else if(mp[i][j] == 'Z')
				{
					zs[k] = (point){i, j, 0};
					k++;
				}
			}
		}

		ans = bfs(n, m, ms, gs, zs);
		printf("%d\n", ans);
	}
	return 0;
}