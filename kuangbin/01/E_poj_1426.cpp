/* AC */
#include <stdio.h>

long long bfs(int num)
{
	long long ans, tep;
	int front, back;
	long long que[1000000];

	que[0] = 1;
	front = 0;
	back = 1;
	while(front != back)
	{
		tep = que[front] * 10;
		if(tep % num == 0)
		{
			ans = tep;
			break;
		}
		que[back] = tep;
		back ++;

		tep += 1;
		if(tep % num == 0)
		{
			ans = tep;
			break;
		}
		que[back] = tep;
		back ++;
		front++;
	}
	return ans;
}

int main()
{
	int num;
	long long ans;

	while(scanf("%d", &num) != EOF)
	// for(num = 1; num <= 200; num++)
	{
		if(num <= 0)
		{
			break;
		}
		ans = bfs(num);
		printf("%lld\n", ans);
		// if(ans % num != 0)
		// {
		// 	printf("false!\n");
		// }
	}
	return 0;
}