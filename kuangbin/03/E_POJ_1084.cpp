/* http://poj.org/problem?id=1084 */
/* AC 412K 16MS */
#include <stdio.h>
#include <string.h>

const int MAX_N = 8;

/* 舞蹈链算法，用于求重复覆盖问题 */
typedef struct dance_link_rep
{
	const static int MAX_ROWS = 2 * MAX_N * MAX_N;
	const static int MAX_COLS = 2 * MAX_N * MAX_N;

	typedef struct node
	{
		int u, d, l, r;
		int row, col;
	} node;

	int rows, cols, node_size;
	node nd[MAX_ROWS * MAX_COLS];
	int row_head[MAX_ROWS], col_nds[MAX_COLS];

	bool is_min_ans;
	int limit;
	int ans, *select_rows;

	void init(int rows, int cols)
	{
		int i;

		this -> rows = rows;
		this -> cols = cols;
		/* 初始化每一列的头节点 */
		for(i = 0; i <= cols; i++)
		{
			nd[i].u = i;
			nd[i].d = i;
			nd[i].l = i - 1;
			nd[i].r = i + 1;
			col_nds[i] = 0;
		}
		nd[0].l = cols;
		nd[cols].r = 0;
		node_size = cols + 1;

		/* 初始化每一行的行指针 */
		for(i = 0; i <= rows; i++)
		{
			row_head[i] = -1;
		}
	}

	void add_node(int row, int col)
	{
		/* nd[node_size]为新添加的节点 */
		nd[node_size].row = row;
		nd[node_size].col = col;

		/* 将新添加的节点与其所在的列连接 */
		nd[node_size].u = col;
		nd[node_size].d = nd[col].d;
		nd[nd[col].d].u = node_size;
		nd[col].d = node_size;

		/* 将新添加的节点与其所在的行连接 */
		if(row_head[row] == -1)
		{
			row_head[row] = node_size;
			nd[node_size].l = node_size;
			nd[node_size].r = node_size;
		}
		else
		{
			int row_first = row_head[row];
			nd[node_size].r = row_first;
			nd[node_size].l = nd[row_first].l;
			nd[nd[row_first].l].r = node_size;
			nd[row_first].l = node_size;
		}
		col_nds[col]++;
		node_size++;
	}

	void remove(int col)
	{
		int i;
		for(i = nd[col].d; i != col; i = nd[i].d)
		{
			nd[nd[i].r].l = nd[i].l;
			nd[nd[i].l].r = nd[i].r;
		}
	}

	void resume(int col)
	{
		int i;
		for(i = nd[col].u; i != col; i = nd[i].u)
		{
			nd[nd[i].l].r = i;
			nd[nd[i].r].l = i;
		}
	}

	/* 计算取得答案最少需要的行数 */
	int get_min_rows()
	{
		int i, j, k, num = 0;
		bool v[MAX_COLS];
		
		for(i = nd[0].r; i != 0; i = nd[i].r)
		{
			v[i] = true;
		}
		for(i = nd[0].r; i != 0; i = nd[i].r)
		{
			if(v[i] == false)
			{
				continue;
			}
			num++;
			for(j = nd[i].d; j != i; j = nd[j].d)
			{
				for(k = nd[j].r; k != j; k = nd[k].r)
				{
					v[nd[k].col] = false;
				}
			}
		}
		return num;
	}

	int dfs(int len)
	{
		int i, j;
		int res, select_col;

		/* 判断是否超过了界限 */
		int mr = get_min_rows();
		if(limit != -1 && len + mr > limit)
		{
			return -1;
		}
		if(is_min_ans == true && ans != -1 && len + mr >= ans)
		{
			return -1;
		}
		/* 当前十字链表没有列 */
		if(nd[0].r == 0)
		{
			return len;
		}
		select_col = nd[0].r;
		for(i = nd[0].r; i != 0; i = nd[i].r)
		{
			if(nd[i].d == i)
			{
				return -1;
			}
			if(col_nds[select_col] > col_nds[i])
			{
				select_col = i;
			}
		}
		for(i = nd[select_col].d; i != select_col; i = nd[i].d)
		{
			if(select_rows != 0)
			{
				select_rows[len] = nd[i].row;
			}
			remove(i);
			for(j = nd[i].r; j != i; j = nd[j].r)
			{
				remove(j);
			}
			res = dfs(len + 1);
			if(res >= 0)
			{
				if(is_min_ans == false)
				{
					return res;
				}
				else if(ans < 0 || ans > res)
				{
					ans = res;
				}
			}
			for(j = nd[i].l; j != i; j = nd[j].l)
			{
				resume(j);
			}
			resume(i);
		}
		return ans;
	}

	/*
	bool is_min_ans: 是否求答案最小值，如果不是，得到一个可行解就返回，默认求最小值。
	int select_rows[]: 用于保存选择的行，取NULL时不保存，默认取NULL。
	int limit：答案的上限，取-1时无上限，默认为-1。
	*/
	int solve(bool is_min_ans = true, int select_rows[] = 0, int limit = -1)
	{
		this->is_min_ans = is_min_ans;
		this->select_rows = select_rows;
		this->limit = limit;
		ans = -1;
		ans = dfs(0);
		return ans;
	}

} dance_link_rep;


dance_link_rep dl;

int main()
{
	int t, n;
	int i, j, k, s, p, x, y, c, flag, ans;
	int rows, cols;
	int ds[2 * MAX_N], dst;
	int ms[2 * MAX_N][2 * MAX_N];
	int as[dl.MAX_ROWS * dl.MAX_COLS][2], ast;

	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d", &n, &dst);
		for(i = 0; i < dst; i++)
		{
			scanf("%d", &ds[i]);
		}
		memset(ms, 0, sizeof(ms));
		for(i = 0, c = 1; i <= 2 * n; i++)
		{
			for(j = !(i % 2); j <= 2 * n; j += 2)
			{
				ms[i][j] = c;
				for(s = 0; s < dst; s++)
				{
					if(c == ds[s])
					{
						ms[i][j] = -1;
						break;
					}
				}
				c++;
			}
		}
		for(i = 0, c = 1; i <= 2 * n; i++)
		{
			for(j = !(i % 2); j <= 2 * n; j += 2)
			{
				ms[i][j] = c;
				for(s = 0; s < dst; s++)
				{
					if(c == ds[s])
					{
						ms[i][j] = -1;
						break;
					}
				}
				c++;
			}
		}
		// for(i = 0; i <= 2 * n; i++)
		// {
		// 	for(j = 0; j <= 2 * n; j++)
		// 	{
		// 		printf("%3d", ms[i][j]);
		// 	}
		// 	printf("\n");
		// }
		// printf("\n");

		c = 1;
		ast = 0;
		for(x = 0; x < 2 * n; x += 2)
		{
			for(y = 0; y < 2 * n; y += 2)
			{
				for(s = 1; s + x / 2 <= n && s + y / 2 <= n; s++)
				{
					k = ast;
					flag = 0;
					i = x;
					j = y + 1;
					for(p = 0; p < s; p++)
					{
						if(ms[i][j] == -1)
						{
							flag = -1;
						}
						as[k][0] = ms[i][j];
						as[k][1] = c;
						k++;
						j += 2;
					}
					i += 1;
					j -= 1;
					for(p = 0; p < s; p++)
					{
						if(ms[i][j] == -1)
						{
							flag = -1;
						}
						as[k][0] = ms[i][j];
						as[k][1] = c;
						k++;
						i += 2;
					}
					i -= 1;
					j -= 1;
					for(p = 0; p < s; p++)
					{
						if(ms[i][j] == -1)
						{
							flag = -1;
						}
						as[k][0] = ms[i][j];
						as[k][1] = c;
						k++;
						j -= 2;
					}
					i -= 1;
					j += 1;
					for(p = 0; p < s; p++)
					{
						if(ms[i][j] == -1)
						{
							flag = -1;
						}
						as[k][0] = ms[i][j];
						as[k][1] = c;
						k++;
						i -= 2;
					}
					if(flag != -1)
					{
						ast = k;
						c++;
					}
				}
			}
		}

		rows = 2 * n * (n + 1);
		cols = c - 1;
		dl.init(rows, cols);

		// int mat[dl.MAX_ROWS][dl.MAX_COLS];
		// memset(mat, 0, sizeof(mat));

		for(i = 0; i < ast; i++)
		{
			// printf("(%d,%d) ", as[i][0], as[i][1]);
			// if(as[i][1] != as[i + 1][1])
			// {
			// 	printf("\n");
			// }
			// mat[as[i][0]][as[i][1]] = 1;
			dl.add_node(as[i][0], as[i][1]);
		}

		// for(i = 1; i <= dl.rows; i++)
		// {
		// 	printf("%2d ", i);
		// 	for(j = 1; j <= dl.cols; j++)
		// 	{
		// 		printf("%d", mat[i][j]);
		// 	}
		// 	printf("\n");
		// }
		ans = dl.solve(true, NULL, -1);
		printf("%d\n", ans);
	}
	return 0;
}