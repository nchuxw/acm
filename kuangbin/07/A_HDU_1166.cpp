/* http://acm.hdu.edu.cn/showproblem.php?pid=1166 */
#include <stdio.h>

const int MAX_N = 50000 + 10;

int num[MAX_N];
int seg_tree[4 * MAX_N];

int build(int root, int left, int right)
{

}

void update(int root, int left, int right, int index, int add)
{

}

int query(int root, int left, int right, int ql, int qr)
{

}

int main()
{
	int cas, t, n, x, y;
	int i, ans;
	char req[20];

	scanf("%d", &t);
	for(cas = 0; cas < t; cas++)
	{
		scanf("%d", &n);
		for(i = 0; i < n; i++)
		{
			scanf("%d", &num[i]);
		}
		build(1, 0, n);

		printf("Case %d:\n", cas);
		getchar();
		while(scanf("%s %d %d", req, &x, &y) != EOF)
		{
			if(req[0] == 'Q')
			{
				ans = query(1, 0, n, x, y);
				printf("%d\n", ans);
			}
			else if(req[0] == 'A')
			{
				update(1, 0, n, x, y);
			}
			else if(req[0] == 'S')
			{
				update(1, 0, n, x, -y);
			}
			else if(req[0] == 'E')
			{
				break;
			}
		}
	}
	return 0;
}