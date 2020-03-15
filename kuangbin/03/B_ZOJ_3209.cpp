/* https://zoj.pintia.cn/problem-sets/91827364500/problems/91827367871 */
#include <stdio.h>
#include <string.h>

const int MAX_COLS = 30 * 30 + 10;
const int MAX_ROWS = 500 + 10;

typedef struct node
{
	int u, d, l, r;
	int row, col;
} node;

int rows, cols, node_size;
node nd[MAX_ROWS * MAX_COLS];
int row_head[MAX_ROWS], col_nds[MAX_COLS];

// int book[MAX_ROWS];
// int map[MAX_ROWS][MAX_ROWS];

// void print()
// {
// 	int i, j;

// 	memset(map, 0, sizeof(map));
// 	printf("\n    ");
// 	for(i = nd[0].r; i != 0; i = nd[i].r)
// 	{
// 		printf("%3d ", i);
// 		map[0][i] = 1;
// 		for(j = nd[i].d; j != i; j = nd[j].d)
// 		{
// 			map[nd[j].row][nd[j].col] = 1;
// 		}
// 	}
// 	printf("\n");
// 	for(i = 1; i <= rows; i++)
// 	{
// 		if(book[i] == 1)
// 		{
// 			continue;
// 		}
// 		printf("%3d ", i);
// 		for(j = 1; j <= cols; j++)
// 		{
// 			if(map[0][j] == 1)
// 			{
// 				printf("%3d ", map[i][j]);
// 			}
// 		}
// 		printf("\n");
// 	}
// }

void init()
{
	int i;

	/* 初始化每一列的头节点 */
	for(i = 0; i <= cols; i++)
	{
		nd[i].u = i;
		nd[i].d = i;
		nd[i].l = i - 1;
		nd[i].r = i + 1;
	}
	nd[0].l = cols;
	nd[cols].r = 0;
	memset(col_nds, 0, sizeof(col_nds)); 
	node_size = cols + 1;

	/* 初始化每一行的行指针 */
	memset(row_head, -1, sizeof(row_head));

	// memset(book, 0, sizeof(book));
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
	int i, j;

	/* 将第col列从十字链表里移除 */
	nd[nd[col].l].r = nd[col].r;
	nd[nd[col].r].l = nd[col].l;

	/* 将与第col列里节点有关的行移除 */
	for(i = nd[col].d; i != col; i = nd[i].d)
	{
		for(j = nd[i].r; j != i; j = nd[j].r)
		{
			nd[nd[j].u].d = nd[j].d;
			nd[nd[j].d].u = nd[j].u;
			col_nds[nd[j].col]--;
		}
		// book[i] = 1;
	}
}

void resume(int col)
{
	int i, j;

	/* 将第col列从十字链表里恢复 */
	nd[nd[col].l].r = col;
	nd[nd[col].r].l = col;

	/* 将与第col列里节点有关的行恢复 */
	for(i = nd[col].d; i != col; i = nd[i].d)
	{
		for(j = nd[i].r; j != i; j = nd[j].r)
		{
			nd[nd[j].u].d = j;
			nd[nd[j].d].u = j;
			col_nds[nd[j].col]++;
		}
		// book[i] = 0;
	}
}

int dfs(int ans[], int len)
{
	int i, j, res, select_col;
	int min;

	/* 当前十字链表没有列 */
	if(nd[0].r == 0)
	{
		return len;
	}
	min = MAX_ROWS;
	for(i = nd[0].r; i != 0; i = nd[i].r)
	{
		if(nd[i].d == i)
		{
			return -1;
		}
		if(min > col_nds[i])
		{
			select_col = i;
			min = col_nds[i];
		}
	}
	select_col = nd[0].r;
	remove(select_col);
	min = MAX_ROWS;
	for(i = nd[select_col].d; i != select_col; i = nd[i].d)
	{
		ans[len] = nd[i].row;
		for(j = nd[i].r; j != i; j = nd[j].r)
		{
			remove(nd[j].col);
		}
		res = dfs(ans, len + 1);
		if(res >= 0 && res < min)
		{
			min = res;
			continue;
		}
		for(j = nd[i].r; j != i; j = nd[j].r)
		{
			resume(nd[j].col);
		}
	}
	resume(select_col);
	if(min == MAX_ROWS)
	{
	    return -1;
	}
	else
	{
	    return min;
	}
}

int main()
{
	int t, n, m, p, x1, x2, y1, y2;
	int i, j, k, len;
	int ans[MAX_ROWS];

	scanf("%d", &t);
	while(t--)
	{
		// scanf("%d %d", &n, &m);
		// cols = n * m;
		// rows = cols / 4;
		// init();
		// k = 0;
		// for(y1 = 0; y1 < m; y1 += 2)
		// {
		// 	for(x1 = 0; x1 < n; x1 += 2)
		// 	{
		// 		x2 = x1 + 2;
		// 		y2 = y1 + 2;
		// 		printf("(%d, %d) (%d, %d): ", x1, y1, x2, y2);
		// 		for(i = y1; i < y2; i++)
		// 		{
		// 			for(j = x1; j < x2; j++)
		// 			{
		// 				printf("(%d %d) ", k, i * n + j + 1);
		// 				add_node(k, i * n + j + 1);
		// 			}
		// 		}
		// 		printf("\n");
		// 		k++;
		// 	}
		// }
		// printf("\n%d\n", k);
		
		scanf("%d %d %d", &n, &m, &p);
		rows = p;
		cols = n * m;
		init();
		for(k = 0; k < p; k++)
		{
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			for(i = y1; i < y2; i++)
			{
				for(j = x1; j < x2; j++)
				{
//					printf("%d %d\n", k, i * n + j + 1);
					add_node(k, i * n + j + 1);
				}
			}
		}
		// print();
		
		len = dfs(ans, 0);
		printf("%d\n", len);
	}
	return 0;
}

/*

3
5 5 1
0 0 5 5

5 5 2
0 0 3 5
2 0 5 5

30 30 5
0 0 30 10
0 10 30 20
0 20 30 30
0 0 15 30
15 0 30 30

1
-1
2

*/
