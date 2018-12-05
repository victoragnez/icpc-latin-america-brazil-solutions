#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 2;
int n, l, r, dp[2][MAXN], mod = 1e9 + 7;

int main(){
	scanf("%d%d%d", &n, &l, &r);
	for(int i = l; i <= r; i++)
		dp[0][i] = 1;
	for(int i = 1; i < n; i++){
		int e = i & 1, o = e ^ 1;
		for(int j = l; j <= r; j++){
			dp[e][j] = dp[o][j + 1] + dp[o][j - 1];
			if(dp[e][j] >= mod)
				dp[e][j] -= mod;
		}
	}
	int ans = 0;
	for(int i = l; i <= r; i++){
		ans += dp[!(n & 1)][i];
		if(ans >= mod)
			ans -= mod;
	}
	printf("%d\n", ans);
}

