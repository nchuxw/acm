/* https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365976 */
/* AC */
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

// char face_mp[7] = {"rgbowy"};
int span_cent[8][2] = {{0, 2}, {1, 5}, {2, 8}, {5, 7}, {8, 6}, {7, 3}, {6, 0}, {3, 1}};
int span_ed[6][12][2] = 
{
	{
		{36,  9}, {39, 12}, {42, 15},
		{ 9, 45}, {12, 48}, {15, 51},
		{45, 35}, {48, 32}, {51, 29},
		{35, 36}, {32, 39}, {29, 42}
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

int dfs(char cube[6][3][3], int deep, int lit, int fs[][2])
{
	int i, j, k, res;
	char next[6][3][3];

	if(deep >= lit)
	{
		for(i = 0; i < 6; i++)
		{
			for(j = 0; j < 3; j++)
			{
				for(k = 0; k < 3; k++)
				{
					if(cube[i][j][k] != cube[i][1][1])
					{
						return 0;
					}
				}
			}
		}
		return 1;
	}

	for(i = 0; i < 6; i ++)
	{
		memcpy(next, cube, sizeof(next));
		cube_span(next, i, 1);
		res = dfs(next, deep + 1, lit, fs);
		if(res != 0)
		{
			fs[deep][0] = i;
			fs[deep][1] = 1;
			return 1;
		}

		memcpy(next, cube, sizeof(next));
		cube_span(next, i, -1);
		res = dfs(next, deep + 1, lit, fs);
		if(res != 0)
		{
			fs[deep][0] = i;
			fs[deep][1] = -1;
			return 1;
		}
	}
	return 0;
}

void print_cube(char cube[6][3][3])
{
	int i, j, k;

	for(i = 0; i < 3; i++)
	{
		printf("   ");
		for(j = 0; j < 3; j++)
		{
			printf("%c", cube[4][i][j]);
		}
		printf("\n");
	}
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 4; j++)
		{
			for(k = 0; k < 3; k++)
			{
				printf("%c", cube[j][i][k]);
			}
		}
		printf("\n");
	}
	for(i = 0; i < 3; i++)
	{
		printf("   ");
		for(j = 0; j < 3; j++)
		{
			printf("%c", cube[5][i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	int t, i, res;
	int ans, fs[10][2];
	char cube[6][3][3];

	scanf("%d", &t);
	while(t--)
	{
		getchar();
		input_cube(cube);

		for(ans = 0; ans <= 5; ans++)
		{
			res = dfs(cube, 0, ans, fs);
			if(res == 1)
			{
				break;
			}
		}
		if(ans > 5)
		{
			printf("-1\n");
			continue;
		}
		printf("%d\n", ans);
		if(ans != 0)
		{
			for(i = 0; i < ans; i++)
			{
				printf("%d %d\n", fs[i][0], fs[i][1]);
			}
		}
	}
	return 0;
}