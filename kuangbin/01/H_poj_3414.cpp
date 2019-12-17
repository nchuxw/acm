/* http://poj.org/problem?id=3414 */
/* AC */
#include <stdio.h>
#include <map>

using namespace std;

const int MAXN = 10000;

typedef struct stat
{
	int a, b;
} stat;

bool operator < (const stat &s1, const stat &s2)
{
	if(s1.a != s2.a)
	{
		return s1.a < s2.a;
	}
	else
	{
		return s1.b < s2.b;
	}
}

int a, b, c;
stat que[MAXN];
int pre[MAXN];
int opt[MAXN];
map<stat, bool> mp;

int bfs()
{
	int i, front, back;
	stat tep, next[6];
	
	que[0] = (stat){0, 0};
	pre[0] = -1;
	opt[0] = -1;
	mp.clear();
	mp[que[0]] = true;
	front = 0;
	back = 1;
	while(front != back)
	{
		tep = que[front];
		next[0] = (stat){a, tep.b};
		next[1] = (stat){tep.a, b};
		next[2] = (stat){0, tep.b};
		next[3] = (stat){tep.a, 0};
		if(tep.a >= b - tep.b)
		{
			next[4].a = tep.a - (b - tep.b);
			next[4].b = b;
		}
		else
		{
			next[4].a = 0;
			next[4].b = tep.a + tep.b;
		}
		if(tep.b >= a - tep.a)
		{
			next[5].b = tep.b - (a - tep.a);
			next[5].a = a;
		}
		else
		{
			next[5].b = 0;
			next[5].a = tep.b + tep.a;
		}
		for(i = 0; i < 6; i++)
		{
			if(mp[next[i]] == false)
			{
				que[back] = next[i];
				opt[back] = i;
				pre[back] = front;
				if(next[i].a == c || next[i].b == c)
				{
					return back;
				}
				back++;
				mp[next[i]] = true;
			}
		}
		front++;
	}
	return -1;
}

int main()
{
	int ans, p;
	int i, j;
	
	while(scanf("%d%d%d", &a, &b, &c) != EOF)
	{
		p = bfs();
		if(p == -1)
		{
			printf("impossible\n");
		}
		ans = 0;
		for(i = p, j = p; pre[j] != -1; j = pre[j], i--)
		{
			opt[i] = opt[j];
			ans++;
		}
		printf("%d\n", ans);
		for(i = i + 1; i <= p; i++)
		{
			if(opt[i] <= 1)
			{
				printf("FILL(%d)\n", opt[i] + 1);
			}
			else if(opt[i] <= 3)
			{
				printf("DROP(%d)\n", opt[i] - 1);
			}
			else if(opt[i] == 4)
			{
				printf("POUR(1,2)\n");
			}
			else if(opt[i] == 5)
			{
				printf("POUR(2,1)\n");
			}
		}
	}
	return 0;
}