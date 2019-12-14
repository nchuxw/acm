/* AC */
#include <stdio.h>

const int MAXN = 100000 + 10;
const int INF = 100000 + 10;

int bfs(int n, int k)
{
	long long next;
	int ans = -1;
	int front, back;
	int que[MAXN];
	int cost[MAXN];
	int book[INF] = {0};

	que[0] = n;
	cost[0] = 0;
	book[n] = 1;
	front = 0;
	back = 1;
	while(front != back)
	{
		next = que[front] * 2;
		if(next >= 0 && next < INF && book[next] == 0)
		{
			if(next == k)
			{
				ans = cost[front] + 1;
				break;
			}
			que[back] = next;
			cost[back] = cost[front] + 1;
			book[next] = 1;
			back++;
		}
		next = que[front] + 1;
		if(next >= 0 && next < INF && book[next] == 0)
		{
			if(next == k)
			{
				ans = cost[front] + 1;
				break;
			}
			que[back] = next;
			cost[back] = cost[front] + 1;
			book[next] = 1;
			back++;
		}
		next = que[front] - 1;
		if(next >= 0 && next < INF && book[next] == 0)
		{
			if(next == k)
			{
				ans = cost[front] + 1;
				break;
			}
			que[back] = next;
			cost[back] = cost[front] + 1;
			book[next] = 1;
			back ++;
		}
		front ++;
	}
	return ans;
}

int main()
{
	int n, k;
	int ans;

	while(scanf("%d%d", &n, &k) != EOF)
	{
		if(k <= n)
		{
			printf("%d\n", n - k);
			continue;
		}

		ans = bfs(n, k);
		printf("%d\n", ans);
	}
	return 0;
}