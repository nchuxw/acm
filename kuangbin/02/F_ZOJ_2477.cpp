/* https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365976 */
#include <stdio.h>
#include <string.h>

void input_cube(char cube[][3][3])
{
	int i, j, k, slen;
	char str[50];

	for(i = 0; i < 3; i++)
	{
		fgets(str, 50, stdin);
		slen = strlen(str);
		for(j = 0, k = 0; j < slen; j++)
		{
			if('a' <= str[j] && str[j] <= 'z')
			{
				str[k] = str[j];
				k++;
			}
		}
		for(j = 0; j < 3; j++)
		{
			cube[4][i][j] = str[j];
		}
	}
	for(i = 0; i < 3; i++)
	{
		fgets(str, 50, stdin);
		slen = strlen(str);
		for(j = 0, k = 0; j < slen; j++)
		{
			if('a' <= str[j] && str[j] <= 'z')
			{
				str[k] = str[j];
				k++;
			}
		}
		for(j = 3; j < 15; j++)
		{
			cube[j / 3 - 1][i][j % 3] = str[j - 3];
		}
	}
	for(i = 0; i < 3; i++)
	{
		fgets(str, 50, stdin);
		slen = strlen(str);
		for(j = 0, k = 0; j < slen; j++)
		{
			if('a' <= str[j] && str[j] <= 'z')
			{
				str[k] = str[j];
				k++;
			}
		}
		for(j = 0; j < 3; j++)
		{
			cube[5][i][j] = str[j];
		}
	}
}

int span_cent[8][2] = {{0, 2}, {1, 5}, {2, 8}, {5, 7}, {8, 6}, {7, 3}, {6, 0}, {3, 1}};
int span_ed[6][12][2] = 
{
	{
		{36,  9}, {29, 12}, {42, 15},
		{ 9, 45}, {12, 48}, {15, 51},
		{45, 35}, {48, 32}, {51, 35},
		{35, 36}, {32, 29}, {35, 42}
	},
	{
		{42, 18}, {43, 21}, {44, 24},
		{18, 47}, {21, 46}, {24, 45},
		{47,  8}, {46,  5}, {45,  2},
		{ 8, 42}, { 5, 43}, { 2, 44}
	},
	{
		{44, 27}, {41, 30}, {38, 33},
		{27, 53}, {30, 50}, {33, 47},
		{53, 17}, {50, 14}, {47, 11},
		{17, 44}, {14, 41}, {11, 38}
	},
	{
		{38,  0}, {37,  3}, {36,  6},
		{ 0, 51}, { 3, 52}, { 6, 53},
		{51, 26}, {52, 23}, {53, 20},
		{26, 38}, {23, 37}, {20, 36}
	},
	{
		{29, 20}, {28, 19}, {27, 18},
		{20, 11}, {19, 10}, {18,  9},
		{11,  2}, {10,  1}, { 9,  0},
		{ 2, 29}, { 1, 28}, { 0, 27}
	},
	{
		{15, 24}, {16, 25}, {17, 26},
		{24, 33}, {25, 34}, {26, 35},
		{33,  6}, {34,  7}, {35,  8},
		{ 6, 15}, { 7, 16}, { 8, 17}
	}
};

void cube_span(char cube[6][3][3] ,int no, int dist)
{
	int i, s, d, sno, dno;
	int sx, sy, sz, dx, dy, dz;
	char src[6][3][3];

	s = (dist == 1) ? 0 : 1;
	d = !s;
	memcpy(src, cube, sizeof(src));
	for(i = 0; i < 12; i++)
	{
		sno = span_ed[no][i][s];
		dno = span_ed[no][i][d];
		sx = sno / 9;
		sy = sno % 9 / 3;
		sz = sno % 3;
		dx = dno / 9;
		dy = dno % 9 / 3;
		dz = dno % 3;
		cube[dx][dy][dz] = src[sx][sy][sz];
	}
	for(i = 0; i < 8; i++)
	{
		sno = span_cent[i][s];
		dno = span_cent[i][d];
		sy = sno / 3;
		sz = sno % 3;
		dy = dno / 3;
		dz = dno % 3;
		cube[no][dy][dz] = src[no][sy][sz];
	}
}

char dest[6][3][3];
int ans, fs[2];

int dfs(char cube[6][3][3], int deep)
{
	int i, j, k, res, flag;
	char next[6][3][3];

	if(deep > 5 || deep >= ans)
	{
		return 0;
	}
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 3; j++)
		{
			for(k = 0; k < 3; k++)
			{
				if(i == 0 && cube[i][j][k] != 'r') goto continue_search;
				if(i == 1 && cube[i][j][k] != 'g') goto continue_search;
				if(i == 2 && cube[i][j][k] != 'b') goto continue_search;
				if(i == 3 && cube[i][j][k] != 'o') goto continue_search;
				if(i == 4 && cube[i][j][k] != 'w') goto continue_search;
				if(i == 5 && cube[i][j][k] != 'y') goto continue_search;
			}
		}
	}
	if(ans > deep)
	{
		ans = deep;
	}
	return 1;
	continue_search:

	flag = 0;
	for(i = 0; i < 6; i ++)
	{
		memcpy(next, cube, sizeof(next));
		cube_span(next, i, 1);
		res = dfs(next, deep + 1);
		if(res != 0)
		{
			fs[0] = i;
			fs[1] = 1;
			flag = 1;
		}

		memcpy(next, cube, sizeof(next));
		cube_span(next, i, -1);
		res = dfs(next, deep + 1);
		if(res != 0)
		{
			fs[0] = i;
			fs[1] = 1;
			flag = 1;
		}
	}
	return flag;
}

int main()
{
	int t, i, res;
	char cube[6][3][3];

	scanf("%d", &t);
	while(t--)
	{
		getchar();
		input_cube(cube);
		// for(i = 0; i < 6; i++)
		// {
		// 	for(j = 0; j < 3; j++)
		// 	{
		// 		for(k = 0; k < 3; k++)
		// 		{
		// 			printf("%c", cube[i][j][k]);
		// 		}
		// 		printf("\n");
		// 	}
		// }
		// printf("\n");

		ans = 10;
		dfs(cube, 0);
		if(ans > 5)
		{
			printf("-1\n");
			continue;
		}
		printf("%d\n", ans);
		if(ans != 0)
		{
			printf("%d %d\n", fs[0], fs[1]);
		}
	}
	return 0;
}

/*

3
      w w w
      w w w
      w w w
r r r g g g b b b o o o
r r r g g g b b b o o o
r r r g g g b b b o o o
      y y y
      y y y
      y y y

      w w w
      w w w
      b b b
r r w g g g y b b o o o
r r w g g g y b b o o o
r r w g g g y b b o o o
      r r r
      y y y
      y y y

      w w w
      w w w
      b b b
r r w g g g y b b o o o
r r w g g g y b b o o o
r r w g g g y b b o o o
      r r r
      y y y
      y y w


*/