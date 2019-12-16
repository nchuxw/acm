/* http://poj.org/problem?id=3087 */
/* AC */
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	int cas, n, c;
	string s1, s2, s12, dest;
	int i, ans;
	map<string, bool> mp;

	scanf("%d", &n);
	for(cas = 1; cas <= n; cas++)
	{
		scanf("%d", &c);
		getchar();
		// scanf("%s%s%s", &s1, &s2, &dest);
		cin >> s1 >> s2 >> dest;
		mp.clear();
		ans = 0;

		s12 = "";
		while(mp[s12] == false)
		{
			mp[s12] = true;
			s12 = "";
			for(i = 0; i < c; i++)
			{
				s12 += s2[i];
				s12 += s1[i];
			}
			ans++;
			if(s12 == dest)
			{
				mp[dest] = true;
				break;
			}
			s1 = s12.substr(0, c);
			s2 = s12.substr(c, 2 * c);
		}
		if(mp[dest] == false)
		{
			printf("%d -1\n", cas);
		}
		else
		{
			printf("%d %d\n", cas, ans);
		}
	}
	return 0;
}