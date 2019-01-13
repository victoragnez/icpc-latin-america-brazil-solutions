#include<bits/stdc++.h>
using namespace std;

const int MAXN = 500 + 1;
int n, p, g1[MAXN][MAXN], g2[MAXN][MAXN];

void solve(int grid[][MAXN]){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(grid[i][j] != 0)
				grid[i][j] = 0;
			else
				grid[i][j] = min(grid[i - 1][j], min(grid[i][j - 1], grid[i - 1][j - 1])) + 1;
		}
	}
}

int main(){
	scanf("%d%d", &n, &p);
	for(int i = 0; i < p; i++){
		int l, c;
		scanf("%d%d", &l, &c);
		g1[l][c]++;
	}
	for(int i = 0; i < p; i++){
		int l, c;
		scanf("%d%d", &l, &c);
		g2[l][c]++;
	}
	solve(g1);
	solve(g2);
	int ans1 = 0, ans2 = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= n; j++){
			ans1 += max(0, g2[i][j] - g1[i][j]);
			ans2 += max(0, g1[i][j] - g2[i][j]);
		}
	}
	printf("%d %d\n", ans1, ans2);
}

