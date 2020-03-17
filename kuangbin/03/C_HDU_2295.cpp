/* http://acm.hdu.edu.cn/showproblem.php?pid=2295 */
#include <stdio.h>
#include <string.h>
#include <math.h>

const int MAX_N = 50 + 5;
const double EXP = 1e-6;

typedef struct point
{
	double x, y;
	double distance(point b)
	{
		return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
	}
} point;

int main()
{
	int t, n, m, k;
	int i;
	double left, right, mid;
	point city[MAX_N], radar[MAX_N];

	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d %d", &n, &m, &k);
		for(i = 0; i < n; i++)
		{
			scanf("%lf %lf", &city[i].x, &city[i].y);
		}
		for(i = 0; i < m; i++)
		{
			scanf("%lf %lf", &radar[i].x, &radar[i].y);
		}
	}

	return 0;
}