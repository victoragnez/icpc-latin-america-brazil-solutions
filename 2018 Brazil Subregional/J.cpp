#include <bits/stdc++.h>
using namespace std;

int n, k, x[101], y[101];
double dp[101][1<<10], ans;
const double INF = 1e20;

double dist(int i, int j){
	return hypot(x[i] - x[j], y[i] - y[j]);
}

int main(){
	ans = INF;	
	for(int i = 0; i < 101; i++)
		for(int j = 0; j < 1<<10; j++) 
			dp[i][j] = INF;
			
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i++)
		scanf("%d%d", x+i, y+i);
		
	for(int i = 0; i < k; i++)
		for(int j = k; j < n; j++)
			dp[j][1<<i] = dist(i,j);
			
	for(int mask = 1; mask < (1<<k); mask++){
		for(int i = k; i < n; i++){
			for(int sub = mask; sub > 0; sub = (sub-1)&mask)
				dp[i][mask] = min(dp[i][mask], dp[i][sub] + dp[i][mask^sub]);
				
			for(int j = k; j < n; j++)
				dp[j][mask] = min(dp[j][mask], dp[i][mask] + dist(i,j));
			
			if(mask == (1<<k)-1)
				ans = min(ans, dp[i][mask]);
		}
	}
	printf("%.5lf\n", ans);
}

