/* http://acm.hdu.edu.cn/showproblem.php?pid=3567 */
/* AC */
#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int MAXN = 362880 + 10;
const int MAXM = 100;
const int FACT[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

int kantuo(int a[], int n)
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
	int val;
	int pot;
} node;

char book[MAXN];
int dir[][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
// int dir[][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
char opt_mp[] = {'d', 'l', 'r', 'u'};

void bfs(node start, int pre[], char opt[])
{
	int i, n = 9;
	int cx, cy, cp, dx, dy, dp;
	int a[10], b[10];
	node nd, next;
	queue<node> que;

	que.push(start);
	pre[start.val] = -1;
	memset(book, 0, sizeof(book));
	book[start.val] = 1;
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
			re_kantuo(a, n, nd.val);
			memcpy(b, a, sizeof(b));
			b[cp] = a[dp];
			b[dp] = 9;
			next.val = kantuo(b, n);
			next.pot = dp;
			if(book[next.val] == 0)
			{
				book[next.val] = 1;
				pre[next.val] = nd.val;
				opt[next.val] = opt_mp[i];
				que.push(next);
			}
		}
	}
}

int str_array(char str[], int a[])
{
	int i, j, n = 9, len, sp;

	len = strlen(str);
	for(i = 0, j = 0; i < len && j < n; i++)
	{
		if(str[i] == 'X')
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
	return sp;
}

char ans[MAXN];
int pre[9][MAXN];
char opt[9][MAXN];

int main()
{
	int i, j, cas, t, n = 9;
	node start, end;
	int a[11], b[11], mp[11];
	char str_s[20], str_e[20];
	char as[10][12] = {"X12345678", "1X2345678", "12X345678", "123X45678", "1234X5678",
						"12345X678", "123456X78", "1234567X8", "12345678X"};

	/* 初始化 */
	for(i = 0; i < n; i++)
	{
		start.pot = str_array(as[i], a);
		start.val = kantuo(a, n);
		bfs(start, pre[i], opt[i]);
	}

	scanf("%d", &t);
	getchar();
	for(cas = 1; cas <= t; cas++)
	{
		fgets(str_s, 20, stdin);
		fgets(str_e, 20, stdin);

		start.pot = str_array(str_s, a);
		str_array(as[start.pot], b);
		for(i = 0; i < n; i++)
		{
			mp[a[i]] = b[i];
		}
		start.val = kantuo(b, n);

		end.pot = str_array(str_e, a);
		for(i = 0; i < n; i++)
		{
			a[i] = mp[a[i]];
		}
		end.val = kantuo(a, n);

		int len = 0;
		int *p = pre[start.pot];
		char *op = opt[start.pot];
		for(i = end.val; i != start.val; i = p[i])
		{
			ans[len] = op[i];
			len++;
		}
		ans[len] = '\0';
		printf("Case %d: %d\n", cas, len);
		for(i = len - 1; i >= 0; i--)
		{
			printf("%c", ans[i]);
		}
		printf("\n");

		/* 不知道为什么，用反向搜索会WA，正向搜索就AC了 */
		/* 可能是路径长度相等的时候，字典序没有保证最小的原因 */
		// end.pot = str_array(str_e, a);
		// str_array(as[end.pot], b);
		// for(i = 0; i < n; i++)
		// {
		// 	mp[a[i]] = b[i];
		// }
		// end.val = kantuo(b, n);

		// start.pot = str_array(str_s, a);
		// for(i = 0; i < n; i++)
		// {
		// 	a[i] = mp[a[i]];
		// }
		// start.val = kantuo(a, n);

		// int len = 0;
		// int *p = pre[end.pot];
		// char *op = opt[end.pot];
		// for(i = start.val; i != end.val; i = p[i])
		// {
		// 	ans[len] = op[i];
		// 	len++;
		// }
		// ans[len] = '\0';
		// printf("Case %d: %d\n", cas, len);
		// printf("%s\n", ans);
	}
	return 0;
}