#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200 + 2, inf = 1e5;
int n, m, ans = inf, grid[MAXN][MAXN], vis[MAXN][MAXN];
const int mx[] = {1, -1, 0, 0}, my[] = {0, 0, 1, -1};

int dfs(int i, int j){
	vis[i][j] = 1;
	int ret = 1;
	for(int k = 0; k < 4; k++){
		int x = i + mx[k], y = j + my[k];
		if(grid[i][j] == grid[x][y] && !vis[x][y])
			ret += dfs(x, y);
	}
	return ret;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &grid[i][j]);
			if(!grid[i][j])
				grid[i][j] = inf;
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(!vis[i][j])
				ans = min(ans, dfs(i, j));
	printf("%d\n", ans);
}

