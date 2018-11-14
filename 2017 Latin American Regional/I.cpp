#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;
const int MAXM = 2e5 + 1;
const int LOGN = 18;

tuple<int, int, int> vet[MAXM];
int n, m, q, comp[MAXN], anc[MAXN][LOGN], val[MAXN][LOGN], nvl[MAXN];
unordered_map<int, int> cost[MAXN];
vector<int> adj[MAXN], custo[MAXN];

int find(int a){
	return a == comp[a] ? a : comp[a] = find(comp[a]);
}

void merge(int a, int b){
	comp[find(a)] = find(b);
}

void dfs(int v, int p){
	for(int i = 0; i < (int)adj[v].size(); i++){
		if(adj[v][i] != p){
			int u = adj[v][i], c = custo[v][i];
			nvl[u] = nvl[v]+1;
			anc[u][0] = v;
			val[u][0] = c;
			for(int j = 1; j < LOGN; j++){
				anc[u][j] = anc[anc[u][j - 1]][j - 1];
				val[u][j] = max(val[u][j - 1], val[anc[u][j - 1]][j - 1]);
			}
			dfs(u,v);
		}
	}
}

int path_max(int u, int v){
	if(nvl[u] < nvl[v])
		swap(u,v);
	int ret = 0;
	for(int i = LOGN-1; i >= 0; i--){
		if(nvl[u] - (1<<i) >= nvl[v]){
			ret = max(ret, val[u][i]);
			u = anc[u][i];
		}
	}
	if(u != v){
		for(int i = LOGN-1; i >= 0; i--){
			if(anc[u][i] != anc[v][i]){
				ret = max(ret, val[u][i]);
				ret = max(ret, val[v][i]);
				u = anc[u][i];
				v = anc[v][i];
			}
		}
		ret = max(ret, val[u][0]);
		ret = max(ret, val[v][0]);
	}
	return ret;
}

int main(){
	iota(comp, comp + MAXN, 0);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++){
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		u--, v--;
		cost[u][v] = cost[v][u] = c;
		vet[i] = make_tuple(c, u, v);
	}
	sort(vet, vet + m);
	
	long long ans = 0;
	for(int i = 0; i < m; i++){
		int c, u, v;
		tie(c, u, v) = vet[i];
		if(find(u) != find(v)){
			merge(u, v);
			adj[u].emplace_back(v);
			adj[v].emplace_back(u);
			custo[u].emplace_back(c);
			custo[v].emplace_back(c);
			ans += c;
		}
	}
	dfs(0, 0);
	scanf("%d", &q);
	while(q--){
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;
		if(anc[u][0] == v || anc[v][0] == u){
			printf("%lld\n", ans);
			continue;
		}
		printf("%lld\n", ans - path_max(u, v) + cost[u][v]);
	}
}

