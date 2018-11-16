#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 6000 + 1;
const ll inf = 1e18;
ll dp[MAXN][MAXN], cost[MAXN][MAXN];
int opt[MAXN][MAXN];

int n;
ll b, c, vet[MAXN], ac[MAXN];

int main(){
	scanf("%d%lld%lld", &n, &b, &c);
	for(int i = 1; i <= n; i++){
		scanf("%lld", vet + i);
		ac[i] = ac[i - 1] + vet[i];
	}
	
	for(int i = 1; i <= n; i++){
		int ptr = i;
		ll cc = 0;
		for(int j = i + 1; j <= n; j++){
			cc += vet[j] * (j - ptr);
			while(ptr < j){
				if(ac[ptr] - ac[i-1] < ac[j] - ac[ptr])
					cc += (ac[ptr] - ac[i-1]) - (ac[j] - ac[ptr]);
				else
					break;
				ptr++;
			}
			cost[i][j] = cc;
		}
	}
	
	for(int p = 1; p <= n; p++)
		dp[0][p] = inf;
	
	for(int k = 1; k <= n; k++)
		for(int p = 0; p < k; p++)
			dp[k][p] = inf;
	
	for(int i = 1; i <= n; i++)
		opt[i][i] = i;
	
	//Knuth optimization
	for(int dif = 1; dif < n; dif++){
		for(int p = dif + 1; p <= n; p++){
			int k = p - dif;
			dp[k][p] = inf;
			for(int r = opt[k][p - 1]; r <= opt[k + 1][p]; r++){
				ll cur = cost[r][p] + dp[k - 1][r - 1];
				if(dp[k][p] > cur){
					dp[k][p] = cur;
					opt[k][p] = r;
				}
			}
		}
	}
	
	for(int i = 1; i <= n; i++)
		printf("%lld%c", i * b + dp[i][n] * c, (i == n) ? '\n' : ' ');
}
