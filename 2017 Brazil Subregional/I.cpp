#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 1;
int n, c, subtree[MAXN];
vector<int> adj[MAXN], cost[MAXN];
long long ans;

void dfs(int v, int p, int cc){
	for(int i = 0; i < (int)adj[v].size(); i++){
		if(p != adj[v][i]){
			dfs(adj[v][i], v, cost[v][i]);
			subtree[v] += subtree[adj[v][i]];
		}
	}
	ans += cc * ((subtree[v] + c - 1) / c);
}

int main(){
	scanf("%d%d", &n, &c);
	for(int i = 0; i < n; i++)
		scanf("%d", subtree + i);
	for(int i = 1; i < n; i++){
		int u, v, cc;
		scanf("%d%d%d", &u, &v, &cc);
		u--;
		v--;
		adj[u].emplace_back(v);
		cost[u].emplace_back(cc);
		adj[v].emplace_back(u);
		cost[v].emplace_back(cc);
	}
	dfs(0, 0, 0);
	printf("%lld\n", 2 * ans);
}
