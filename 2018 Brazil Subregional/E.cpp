#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 1;

char a[MAXN], b[MAXN];

int main(){
	scanf("%s%s", a, b);
	int n = (int)strlen(a), m = (int)strlen(b), ans = 0;
	for(int i = 0; i <= n-m; i++){
		int ok = 1;
		for(int j = 0; j < m; j++){
			if(b[j] == a[i+j]){
				ok = 0;
				break;
			}
		}
		ans += ok;
	}
	printf("%d\n",ans);
}
