/* http://poj.org/problem?id=1236 */
/* AC 0MS 356K */
#include <stdio.h>
#include <string.h>

const int MAX_N = 100 + 10;

int n;
int mp[MAX_N][MAX_N];
int vis[MAX_N], vis_t;
int st[MAX_N], st_top;
int in_st[MAX_N];
int low[MAX_N];
int belong[MAX_N], ccn;

int tarjan(int v)
{
	int i, k;

	vis[v] = vis_t;
	low[v] = vis_t;
	vis_t++;
	st_top++;
	st[st_top] = v;
	in_st[v] = 1;
	for(i = 0; i < n; i++)
	{
		if(mp[v][i] == 0)
		{
			continue;
		}
		if(vis[i] == 0)
		{
			tarjan(i);
			if(low[v] > low[i])
			{
				low[v] = low[i];
			}
		}
		else if(in_st[i] == 1 && low[v] > vis[i])
		{
			low[v] = vis[i];
		}
	}
	if(low[v] == vis[v])
	{
		k = -1;
		while(k != v)
		{
			k = st[st_top];
			st_top--;
			in_st[k] = 0;
			belong[k] = ccn;
			// printf("%d ", k);
		}
		ccn++;
		// printf("\n");
	}
}

int main()
{
	int i, j, k;
	int d_in0, d_out0;
	int d_in[MAX_N], d_out[MAX_N];

	scanf("%d", &n);
	memset(mp, 0, sizeof(mp));
	for(i = 0; i < n; i++)
	{
		while(scanf("%d", &k) != EOF && k !=0)
		{
			mp[i][k - 1] = 1;
		}
	}

	/* 计算强连通分量 */
	memset(vis, 0, sizeof(vis));
	memset(in_st, 0, sizeof(in_st));
	ccn = 0;
	for(i = 0; i < n; i++)
	{
		if(vis[i] == 0)
		{
			st_top = -1;
			vis_t = 1;
			tarjan(i);
		}
	}
	// printf("%d\n", ccn);
	// for(i = 0; i < n; i++)
	// {
	// 	printf("%d ", belong[i]);
	// }
	// printf("\n");

	/* 计算每个强连通分量的入度和出度 */
	memset(d_in, 0, sizeof(d_in));
	memset(d_out, 0, sizeof(d_out));
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(mp[i][j] == 1 && belong[i] != belong[j])
			{
				d_in[belong[j]]++;
				d_out[belong[i]]++;
			}
		}
	}

	d_in0 = 0;
	d_out0 = 0;
	for(i = 0; i < ccn; i++)
	{
		if(d_in[i] == 0)
		{
			d_in0++;
		}
		if(d_out[i] == 0)
		{
			d_out0++;
		}
	}

	if(ccn == 1)
	{
		printf("1\n0\n");
	}
	else
	{
		printf("%d\n%d\n", d_in0, (d_in0 > d_out0) ? d_in0 : d_out0);
	}

	return 0;
}

/*

6
2 3 0
4 0
4 5 0
1 6 0
6 0
0

5
2 4 3 0
4 5 0
0
0
1 0

*/