#include<bits/stdc++.h>
using namespace std;

int main(){
	int n, c, s, cur = 1, ans = 0;
	scanf("%d%d%d", &n, &c, &s);
	s %= n;
	if(s == cur)
		ans++;
	for(int i = 0; i < c; i++){
		int v;
		scanf("%d", &v);
		cur = (cur + n + v) % n;
		if(cur == s)
			ans++;
	}
	printf("%d\n", ans);
}
