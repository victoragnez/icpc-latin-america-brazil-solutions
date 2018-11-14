#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;

char s[MAXN];
int n, cnt[MAXN], ans;

int main(){
	scanf("%s", s);

	n = (int)strlen(s);
	for(int i = 1; i < n; i++)
		cnt[__gcd(i,n)]++;

	for(int d = 1; d < n; d++){
		if(cnt[d]){
			int ok = 0;
			for(int j = 0; j < d; j++){
				if(s[j]=='R'){
					int cur = 1;
					int v = (j + d) % n;
					while(v != j){
						if(s[v] != 'R'){
							cur = 0;
							break;
						}
						v = (v + d) % n;
					}
					if(cur){
						ok = 1;
						break;
					}
				}
			}
			if(ok)
				ans += cnt[d];
		}
	}
	
	printf("%d\n", ans);
}
