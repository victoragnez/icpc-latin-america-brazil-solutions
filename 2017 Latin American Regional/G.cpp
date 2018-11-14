#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 1;

int n, x[MAXN], y[MAXN], f[MAXN];
ll dp[MAXN][2][2], mod = 1e9 + 7;

int get(int a, int b, int v){
	if(v == -1)
		return !(a & b);
	return v;
}

void solve(int v){
	if(!v){
		dp[v][0][0] = dp[v][1][1] = 1;
		return;
	}
	solve(x[v]);
	solve(y[v]);
	int vet[] = {0, 1};
	for(int ca : vet){
		for(int ra : vet){
			for(int cb : vet){
				for(int rb : vet){
					int cc = get(ca, cb, -1), rc = get(ra, rb, f[v]);
					dp[v][cc][rc] = (dp[v][cc][rc] + dp[x[v]][ca][ra] * dp[y[v]][cb][rb]) % mod;
				}
			}
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d%d", &x[i], &y[i], &f[i]);
	solve(1);
	printf("%lld\n", (dp[1][0][1] + dp[1][1][0])%mod );
}

