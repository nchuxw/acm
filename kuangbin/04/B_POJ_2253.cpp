/* http://poj.org/problem?id=2253 */
/* AC 0MS 336K */
#include <stdio.h>
#include <math.h>

const int MAX_N = 200 + 10;

typedef struct point
{
	int x, y;
	double distance(point p)
	{
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
} point;

int n;
point p[MAX_N];

double dijkstra(int start, int end)
{
	int i, j, k;
	double min, max;
	int book[MAX_N];
	double dist[MAX_N];

	for(i = 0; i <= n; i++)
	{
		dist[i] = p[start].distance(p[i]);
		book[i] = 0;
	}
	dist[start] = 0.0;
	book[start] = 1;

	for(i = 1; i < n; i++)
	{
		min = 1e10;
		for(j = 0; j < n; j++)
		{
			if(book[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}
		if(k == end)
		{
			return dist[k];
		}
		book[k] = 1;
		for(j = 0; j < n; j++)
		{
			if(book[j] == 0)
			{
				/* 计算起点经过k点到达j点的路径最大值 */
				max = p[k].distance(p[j]);
				if(dist[k] > max)
				{
					max = dist[k];
				}
				if(dist[j] > max)
				{
					dist[j] = max;
				}
			}
		}
	}
	return -1;
}

int main()
{
	int i, t;
	double ans;

	for(t = 1; scanf("%d", &n) != EOF && n >= 2; t++)
	{
		for(i = 0; i < n; i++)
		{
			scanf("%d %d", &p[i].x, &p[i].y);
		}
		ans = dijkstra(0, 1);
		printf("Scenario #%d\n", t);
		printf("Frog Distance = %.3f\n\n", ans);
	}
	return 0;
}