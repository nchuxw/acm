/* http://poj.org/problem?id=1287 */
/* AC 16MS 400K */
#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAX_N = 50 + 10;

typedef struct edge
{
	int a, b, w;
} edge;

int cmp(edge a, edge b)
{
	return a.w < b.w;
}

int find_root(int set[], int i)
{
	if(set[i] != i)
	{
		set[i] = find_root(set, set[i]);
	}
	return set[i];
}

int kruskal(edge e[], int n, int m)
{
	int i, k, ar, br;
	int ans = 0;
	int set[MAX_N];

	sort(e, e + m, cmp);
	for(i = 0; i < MAX_N; i++)
	{
		set[i] = i;
	}
	k = 1;
	for(i = 0; i < m && k < n; i++)
	{
		ar = find_root(set, e[i].a);
		br = find_root(set, e[i].b);
		if(ar != br)
		{
			set[ar] = br;
			ans += e[i].w;
			k++;
		}
	}
	if(k < n)
	{
		return -1;
	}
	return ans;
}

int n, m;
edge e[MAX_N * MAX_N];

int main()
{
	int i, a, b, w, ans;

	while(scanf("%d", &n) != EOF && n > 0)
	{
		scanf("%d", &m);
		for(i = 0; i < m; i++)
		{
			scanf("%d %d %d", &a, &b, &w);
			e[i] = (edge){a, b, w};
		}

		ans = kruskal(e, n, m);
		printf("%d\n", ans);
	}
	return 0;
}