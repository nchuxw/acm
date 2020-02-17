/* http://acm.hdu.edu.cn/showproblem.php?pid=1067 */
#include <stdio.h>
#include <string.h>
#include <queue>
#include <map>

using namespace std;

typedef struct node
{
	char index[4];
	char a[4][7];
	int t;
} node;

typedef struct mapnd
{
	char a[4][7];
} mapnd;

int operator < (const mapnd a, const mapnd b)
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 7; j++)
		{
			if(a.a[i][j] != b.a[i][j])
			{
				return a.a[i][j] < b.a[i][j];
			}
		}
	}
}

void print_node(node nd)
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		printf("%d %d\n", nd.index[i] / 10, nd.index[i] % 10);
	}
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 7; j++)
		{
			printf("%d ", nd.a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int is_end(char a[4][7])
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 6; j++)
		{
			if(a[i][j] / 10 != i + 1 || a[i][j] % 10 != j + 2)
			{
				return 0;
			}
		}
	}
	return 1;
}

int solve(node start)
{
	int i, j, k, tx, ty, cx, cy, cnum;
	queue<node> que;
	map<mapnd, char> mp;
	node tep;
	mapnd mpnd;

	que.push(start);
	mp.clear();
	memcpy(mpnd.a, start.a, sizeof(mpnd.a));
	mp[mpnd] = 1;
	while(que.empty() == false)
	{
		tep = que.front();
		que.pop();
		tep.t++;
		for(k = 0; k < 4; k++)
		{
			tx = tep.index[k] / 10;
			ty = tep.index[k] % 10;
			if(ty == 0)
			{
				cnum = tx * 10 + 12;
			}
			else
			{
				cnum = tep.a[tx][ty - 1] + 1;
			}
			if(cnum % 10 == 8 || cnum == 1)
			{
				continue;
			}
			for(i = 0, j = 7; i < 4 && j == 7; i++)
			{
				for(j = 0; j < 7; j++)
				{
					if(tep.a[i][j] == cnum)
					{
						cx = i;
						cy = j;
						break;
					}
				}
			}
			tep.a[tx][ty] = cnum;
			tep.a[cx][cy] = 0;
			memcpy(mpnd.a, tep.a, sizeof(mpnd.a));
			if(mp.count(mpnd) == 1)
			{
				continue;
			}
			mp[mpnd] = 1;
			tep.index[k] = cx * 10 + cy;
			// print_node(tep);
			if(is_end(tep.a))
			{
				return tep.t;
			}
			que.push(tep);
			tep.index[k] = tx * 10 + ty;
			tep.a[tx][ty] = 0;
			tep.a[cx][cy] = cnum;
			// print_node(tep);
		}
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
				start.a[i][j] = (char)in;
				if(start.a[i][j] % 10 == 1)
				{
					start.a[i][j] = 0;
					start.index[k] = i * 10 + j;
					k++;
				}
			}
		}
		if(is_end(start.a))
		{
			printf("0\n");
			continue;
		}
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