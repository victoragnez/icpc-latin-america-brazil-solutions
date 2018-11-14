#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, ans = 0;
	scanf("%d", &n);
	while(n--){
		int v;
		scanf("%d", &v);
		ans += (v!=1);
	}
	printf("%d\n", ans);
}
