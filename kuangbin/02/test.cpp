#include<iostream>
#include<cstdio>  
#include<cstring>  
#include<algorithm>
using namespace std;
 
char magic[60];  
int cube[6][9] = {  
    {4,0,1,2,3,5,6,7,8},{22,9,10,11,21,23,33,34,35},{25,12,13,14,24,26,36,37,38},  
    {28,15,16,17,27,29,39,40,41},{31,18,19,20,30,32,42,43,44},{49,45,46,47,48,50,51,52,53}  
};   
const int rot[12][20]={  
         {11,23,35,34,33,21, 9,10,51,48,45,36,24,12, 6, 3, 0,20,32,44}, //只有20个需要改变，每个中心无需改变   
         { 9,10,11,23,35,34,33,21,36,24,12, 6, 3, 0,20,32,44,51,48,45},  
         {14,13,26,38,37,36,24,12,45,46,47,39,27,15, 8, 7, 6,11,23,35},  
         {12,24,13,14,26,38,37,36,39,27,15, 8, 7, 6,11,23,35,45,46,47},  
         {17,29,41,40,39,27,15,16,47,50,53,42,30,18, 2, 5, 8,14,26,38},  
         {15,16,17,29,41,40,39,27,42,30,18, 2, 5, 8,14,26,38,47,50,53},  
         {18,19,20,32,44,43,42,30,53,52,51,33,21, 9, 0, 1, 2,17,29,41},  
         {42,30,18,19,20,32,44,43,33,21, 9, 0, 1, 2,17,29,41,53,52,51},  
         { 0, 1, 2, 5, 8, 7, 6, 3,12,13,14,15,16,17,18,19,20, 9,10,11},  
         { 6, 3, 0, 1, 2, 5, 8, 7,15,16,17,18,19,20, 9,10,11,12,13,14},  
         {45,46,47,50,53,52,51,48,44,43,42,41,40,39,38,37,36,35,34,33},  
         {51,48,45,46,47,50,53,52,41,40,39,38,37,36,35,34,33,44,43,42}  
};  
int ans[2][10],limit;
bool check()//检查是否拼完
{
	for(int i=0;i<6;i++)
	 for(int j=0;j<8;j++)
	  if(magic[cube[i][j]]!=magic[cube[i][j+1]])
		  return false;
	return true;
}
 
void rotate(int x)//用异或的好处：相当于奇偶互换模拟顺逆时针，1和2互换，3和4互换，以此类推
{
	int h = x^1;
	char temp[60];
	memcpy(temp,magic,sizeof(magic));
	for(int i=0;i<20;i++)
	 magic[rot[x][i]] = temp[rot[h][i]];//旋转时异或的好处就体现出来了
}

int num1, num2;
 
int dfs(int tot)
{
	num1++;
	if(tot>=limit) return check();
	num2++;
	char temp[60];
	memcpy(temp,magic,sizeof(magic));
	for(int i=0;i<12;i++)
	{
		rotate(i);
		ans[0][tot] = i/2;
		ans[1][tot] = (i&1) ? -1 : 1;
		if(dfs(tot+1)) return 1;
		memcpy(magic,temp,sizeof(temp));
	}
}
 
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		for(int i=0;i<54;i++)
		{
			while(1)
			{
				char ch = getchar();
				if(isalpha(ch)) {
					magic[i] = ch;
					break;
				}
			}
		}

		magic[54] = '\0';
		printf("%s\n", magic);

		// num1 = 0;
		// num2 = 0;
		// for(limit=0;limit<=6;limit++)
		// {
		// 	if(limit==6) cout<<"-1"<<endl;
		// 	else if(dfs(0)) {
		// 		cout<<limit<<endl;
		// 		for(int i=0;i<limit;i++)
		// 		 cout<<ans[0][i]<<" "<<ans[1][i]<<endl;//输出步骤
		// 		break;
		// 	}
		// }
		// printf("num1 = %d, num2 = %d\n\n", num1, num2);
	}
	return 0;
}