/* http://poj.org/problem?id=2236 */
/* AC 3329MS 328K */
#include <stdio.h>
#include <math.h>

const int MAX_N = 1000 + 10;

typedef struct point
{
	int x, y;
	double distance(point p)
	{
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
} point;

int find_root(int set[], int i)
{
	if(set[i] != i)
	{
		set[i] = find_root(set, set[i]);
	}
	return set[i];
}

int main()
{
	int n, d;
	char opt;
	int i, j, a, b, ar, br;
	int set[MAX_N], book[MAX_N];
	point p[MAX_N];

	scanf("%d %d", &n, &d);
	for(i = 1; i <= n; i++)
	{
		scanf("%d %d", &p[i].x, &p[i].y);
		set[i] = i;
		book[i] = 0;
	}
	while(scanf("%c", &opt) != EOF)
	{
		if(opt == 'O')
		{
			scanf("%d", &a);
			ar = find_root(set, a);
			for(i = 1; i <= n; i++)
			{
				if(book[i] == 1 && p[i].distance(p[a]) <= (double)d)
				{
					br = find_root(set, i);
					set[br] = ar;
				}
			}
			book[a] = 1;
		}
		else if(opt == 'S')
		{
			scanf("%d %d", &a, &b);
			if(book[a] == 0 || book[b] == 0)
			{
				printf("FAIL\n");
				continue;
			}
			ar = find_root(set, a);
			br = find_root(set, b);
			if(ar == br)
			{
				printf("SUCCESS\n");
			}
			else
			{
				printf("FAIL\n");
			}
		}
	}
	return 0;
}

/*

4 1
0 1
0 2
0 3
0 4
O 1
O 2
O 4
S 1 4
O 3
S 1 4

*/