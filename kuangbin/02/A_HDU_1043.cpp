/* http://acm.hdu.edu.cn/showproblem.php?pid=1043 */
#include <stdio.h>
#include <string.h>
#include <string>
#include <queue>

using namespace std;

const int MAXN = 362880 + 10;
const int MAXM = 100;
const int FACT[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

int kantuo(char a[], int n)
{
	int i, j, k, num = 0;
	for(i = 0; i < n; i++)
	{
		k = 0;
		for(j = i + 1; j < n; j++)
		{
			if(a[j] < a[i])
			{
				k++;
			}
		}
		num += (k * FACT[n - i - 1]);
	}
	return num;
}

void re_kantuo(int a[], int n, int num)
{
	int i, j, k;
	char book[11];
	memset(book, 0, sizeof(book));
	for(i = 0; i < n; i++)
	{
		k = num / FACT[n - i - 1] + 1;
		num = num % FACT[n - i - 1];
		for(j = 1; j <= n && k > 0; j++)
		{
			if(book[j] == 0)
			{
				k--;
			}
		}
		j--;
		a[i] = j;
		book[j] = 1;
	}
}

typedef struct node
{
	char a[10];
	int val;
	char pot;
} node;

char book[MAXN];
string ans[MAXN];
int dir[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
char opt_mp[] = {'l', 'u', 'r', 'd'};

int bfs()
{
	int i, n = 9, k = 1;
	int cx, cy, cp, dx, dy, dp;
	node nd, next;
	queue<node> que;

	for(i = 0; i < n; i++)
	{
		nd.a[i] = i + 1;
	}
	nd.pot = 8;
	nd.val = 0;
	que.push(nd);
	ans[0] = "";
	memset(book, 0, sizeof(book));
	book[0] = 1;
	while(que.empty() == false)
	{
		nd = que.front();
		que.pop();
		cp = nd.pot;
		cx = cp / 3;
		cy = cp % 3;
		for(i = 0; i < 4; i++)
		{
			dx = cx + dir[i][0];
			dy = cy + dir[i][1];
			if(dx < 0 || dx >= 3 || dy < 0 || dy >= 3)
			{
				continue;
			}
			dp = 3 * dx + dy;
			next = nd;
			next.a[cp] = nd.a[dp];
			next.a[dp] = 9;
			next.val = kantuo(next.a, n);
			next.pot = dp;
			if(book[next.val] == 0)
			{
				book[next.val] = 1;
				ans[next.val] = opt_mp[i] + ans[nd.val];
				que.push(next);
				// k++;
			}
		}
	}
	// printf("%d\n", k);
	return -1;
}

int main()
{
	int i, j, n = 9;
	int len, sp, res;
	char a[11];
	char str[50];

	bfs();
	while(fgets(str, 50, stdin) != NULL)
	{
		len = strlen(str);
		for(i = 0, j = 0; i < len && j < n; i++)
		{
			if(str[i] == 'x')
			{
				a[j] = 9;
				sp = j;
				j++;
			}
			if(str[i] >= '1' && str[i] <= '8')
			{
				a[j] = (int)(str[i] - '0');
				j++;
			}
		}
		
		res = kantuo(a, n);
		if(book[res] == 0)
		{
			printf("unsolvable\n");
		}
		else
		{
			for(i = 0; i < ans[res].length(); i++)
			{
				printf("%c", ans[res][i]);
			}
			printf("\n");
		}
	}
	return 0;
}