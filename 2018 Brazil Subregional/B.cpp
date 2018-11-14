#include <bits/stdc++.h>
using namespace std;

int dp[101][101];

inline bool ok(int a, int b){
	return a > 0 && b > 0 && a != b;
}

int solve(int i, int j){
	if(i > j)
		swap(i,j);
		
	if(dp[i][j] != -1)
		return dp[i][j];
		
	if(i == 1 && j == 2)
		return dp[i][j] = 0;
	
	char jav[300];
	memset(jav, 0, sizeof(jav));
	
	for(int k = 1; k < max(i,j)+1; k++){
		if(k <= i && ok(i-k,j))
			jav[solve(i-k,j)] = 1;
		if(k <= j && ok(i,j-k))
			jav[solve(i,j-k)] = 1;
		if(k <= i && k <= j && ok(i-k,j-k))
			jav[solve(i-k,j-k)] = 1;
	}
	
	for(int k = 0; k < 3*max(i,j); k++)
		if(!jav[k])
			return dp[i][j] = k;
			
	assert(0);
	return -1;
}

int main(){
	memset(dp, -1, sizeof(dp));
	
	int n, ans = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		if(a==b){
			puts("Y");
			return 0;
		}
		ans ^= solve(a,b);
	}
	
	if(ans)
		puts("Y");
	else
		puts("N");
}

