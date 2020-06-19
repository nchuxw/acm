/* http://acm.hdu.edu.cn/showproblem.php?pid=4081 */
/* AC 109MS 16968K */
#include <stdio.h>
#include <string.h>
#include <math.h>

const int MAX_N = 1000 + 10;

typedef struct node
{
	int x, y, p;
} node;

int n;
node nd[MAX_N];
int mst[MAX_N];
double mp[MAX_N][MAX_N];
double maxd[MAX_N][MAX_N];

double prim()
{
	int i, j, k;
	double min, mst_l;
	double dist[MAX_N];

	for(i = 0; i < n; i++)
	{
		dist[i] = mp[0][i];
		mst[i] = 0;
	}
	dist[0] = -1;
	memset(maxd, 0, sizeof(maxd));

	mst_l = 0;
	for(i = 1; i < n; i++)
	{
		min = 1e10;
		for(j = 1; j < n; j++)
		{
			if(dist[j] != -1 && min > dist[j])
			{
				min = dist[j];
				k = j;
			}
		}
		if(min == 1e10)
		{
			return -1;
		}
		mst_l += min;
		dist[k] = -1;
		for(j = 0; j < n; j++)
		{
			if(dist[j] == -1 && j != k)
			{
				int pre = mst[k];
				maxd[j][k] = (maxd[j][pre] > mp[pre][k]) ? maxd[j][pre] : mp[pre][k];
				maxd[k][j] = maxd[j][k];
			}
			if(dist[j] != -1 && dist[j] > mp[k][j])
			{
				dist[j] = mp[k][j];
				mst[j] = k;
			}
		}
	}
	return mst_l;
}

double solve()
{
	int i, j;
	double mst_l, mst_sl, temp, ans;

	mst_l = prim();
	ans = 0;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(i == j)
			{
				continue;
			}
			temp = mst_l - maxd[i][j];
			if(ans < (nd[i].p + nd[j].p) / temp)
			{
				ans = (nd[i].p + nd[j].p) / temp;
			}
		}
	}
	return ans;
}

int main()
{
	int t, i, j;
	double ans;

	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(i = 0; i < n; i++)
		{
			scanf("%d %d %d", &nd[i].x, &nd[i].y, &nd[i].p);
		}
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				mp[i][j] = pow(nd[i].x - nd[j].x, 2) + pow(nd[i].y - nd[j].y, 2);
				mp[i][j] = sqrt(mp[i][j]);
				mp[j][i] = mp[i][j];
			}
		}
		ans = solve();
		printf("%.2f\n", ans);
	}
	return 0;
}

/*
2
4
1 1 20
1 2 30
200 2 80
200 1 100
3
1 1 20
1 2 30
2 2 40

65.00
70.00

*/