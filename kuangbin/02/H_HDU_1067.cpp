/* http://acm.hdu.edu.cn/showproblem.php?pid=1067 */
/* AC */
#include <stdio.h>
#include <string.h>
#include <string>
#include <queue>
#include <map>

using namespace std;

typedef struct node
{
	char index[4];
	char a[30];
	int t;
} node;

void print_node(node nd)
{
	int i, j;
	for(i = 0; i < 28; i++)
	{
		if(i % 7 == 0)
		{
			printf("%d ", i / 7 * 10 + 11);
		}
		if(nd.a[i] == 1)
		{
			printf("## ");
		}
		else
		{
			printf("%d ", nd.a[i]);
		}
		if(i % 7 == 6)
		{
			printf("\n");
		}
	}
}

int solve(node start)
{
	int i, j, k, si, di, dnum;
	node tep;
	queue<node> que;
	map<string, bool> mp;
	char end[30] = 
	{
		12, 13, 14, 15, 16, 17, 1,
		22, 23, 24, 25, 26, 27, 1,
		32, 33, 34, 35, 36, 37, 1,
		42, 43, 44, 45, 46, 47, 1, 0
	};

	if(strcmp(start.a, end) == 0)
	{
		return 0;
	}
	que.push(start);
	mp[start.a] = true;
	while(que.empty() == false)
	{
		for(k = 0; k < 4; k++)
		{
			tep = que.front();
			si = tep.index[k];
			dnum = (si % 7 == 0) ? si / 7 * 10 + 12 : tep.a[si - 1] + 1;
			if(dnum == 2 || dnum % 10 == 8)
			{
				// print_node(tep);
				// printf("%d不可以换\n\n", si);
				continue;
			}
			for(i = 0; i < 28; i++)
			{
				if(tep.a[i] == dnum)
				{
					di = i;
					break;
				}
			}
			tep.a[di] = 1;
			tep.a[si] = dnum;
			tep.index[k] = di;
			tep.t++;
			if(strcmp(tep.a, end) == 0)
			{
				// print_node(tep);
				// printf("找到了\n\n");
				return tep.t;
			}
			if(mp.count(tep.a) == 1)
			{
				// print_node(tep);
				// printf("出现过\n\n");
				continue;
			}
			// print_node(que.front());
			// printf("index: ");
			// for(i = 0; i < 4; i++)
			// {
			// 	printf("%d ", que.front().index[i]);
			// }
			// printf("\n%d --> %d, %d\n", dnum, si, k);
			// print_node(tep);
			// printf("\n");
			mp[tep.a] = true;
			que.push(tep);
		}
		que.pop();
	}
	return -1;
}

int main()
{
	int n, i, j, k, ans, in;
	node start;
	
	scanf("%d", &n);
	while(n--)
	{
		k = 0;
		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 7; j++)
			{
				scanf("%d", &in);
				start.a[i * 7 + j] = (char)in;
				if(start.a[i * 7 + j] % 10 == 1)
				{
					start.a[i * 7 + j] = 1;
					start.index[k] = i * 7 + j;
					k++;
				}
			}
		}
		start.a[28] = '\0';
		start.t = 0;
		ans = solve(start);
		printf("%d\n", ans);
	}
	return 0;
}

/* 

5

12 13 14 15 16 17 21
22 23 24 25 26 27 31
32 33 34 35 36 37 41
42 43 44 45 46 47 11

12 13 14 15 21 31 16
22 23 24 25 26 27 17
32 33 34 35 36 37 41
42 43 44 45 46 47 11

26 31 13 44 21 24 42
17 45 23 25 41 36 11
46 34 14 12 37 32 47
16 43 27 35 22 33 15

17 12 16 13 15 14 11
27 22 26 23 25 24 21
37 32 36 33 35 34 31
47 42 46 43 45 44 41

27 14 22 35 32 46 33
13 17 36 24 44 21 15
43 16 45 47 23 11 26
25 37 41 34 42 12 31



*/