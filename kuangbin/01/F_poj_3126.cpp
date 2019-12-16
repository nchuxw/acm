/* http://poj.org/problem?id=3126 */
/* AC */
#include <stdio.h>
#include <string.h>

const int MAXN = 10000 + 10;

int prime[MAXN];

void get_prime(int prime[], int n)
{
	int i, j;
	memset(prime, -1, sizeof(int) * n);
	prime[0] = 0;
	prime[1] = 0;
	for(i = 2; i < n; i++)
	{
		if(prime[i] != 0)
		{
			for(j = i * i; j < n; j += i)
			{
				prime[j] = 0;
			}
		}
	}
}

int solve(int src, int dest)
{
	int i, tep, ans = -1;
	int que[MAXN], cost[MAXN], book[MAXN];
	int front, back;

	if(src == dest)
	{
		return 0;
	}
	memset(book, 0, sizeof(book));
	que[0] = src;
	cost[0] = 0;
	book[src] = 1;
	front = 0;
	back = 1;
	while(front != back)
	{
		tep = que[front];
		for(int k = 1; k <= 1000; k *= 10)
		{
			int f = tep / (k * 10);
			int b = tep % k;
			for(i = (k == 1000) ? 1 : 0; i < 10; i++)
			{
				int num = f * k * 10 + i * k + b;
				if(num == dest)
				{
					ans = cost[front] + 1;
					return ans;
				}
				if(prime[num] != 0 && book[num] == 0)
				{
					que[back] = num;
					cost[back] = cost[front] + 1;
					book[num] = 1;
					back++;
				}
			}
		}
		front++;
	}
	return -1;
}

int main()
{
	int n, src, dest;
	int i, ans;

	get_prime(prime, MAXN);
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		scanf("%d%d", &src, &dest);
		ans = solve(src, dest);
		if(ans == -1)
		{
			printf("Impossible\n");
		}
		else
		{
			printf("%d\n", ans);
		}
	}
	return 0;
}