#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;
const int LOGN = 18;

vector<int> adj[MAXN];
int nvl[MAXN], anc[MAXN][LOGN];

void dfs(int v, int pr){
	for(int i = 0; i < (int)adj[v].size(); i++){
		if(adj[v][i] != pr){
			int u = adj[v][i];
			nvl[u] = nvl[v] + 1;
			anc[u][0] = v;
			for(int j = 1; j < LOGN; j++)
				anc[u][j] = anc[anc[u][j-1]][j-1];
			dfs(u, v);
		}
	}
}

int moveUp(int v, int diff){
	for(int j = 0; j < LOGN; j++)
		if(diff & (1<<j))
			v = anc[v][j];
	return v;
}

int LCA(int u, int v){
	if(nvl[u] < nvl[v])
		swap(u,v);
	u = moveUp(u, nvl[u] - nvl[v]);
	if(u == v)
		return u;
	for(int i = LOGN - 1; i >= 0; i--){
		if(anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}
	}
	return anc[u][0];
}

vector<pair<int,int> > get(int a, int b){
	int lca = LCA(a,b);
	if(nvl[a] > nvl[b])
		swap(a,b);
	
	vector<pair<int,int> > ret;
	ret.emplace_back(make_pair(b,lca));
	
	if(lca == a)
		return ret;
	
	lca = moveUp(a, nvl[a] - nvl[lca] - 1);
	ret.emplace_back(make_pair(a,lca));
	
	return ret;
}

int query(pair<int,int> c1, pair<int, int> c2){
	int lca = LCA(c1.first, c2.first);
	return max(0, nvl[lca] - max(nvl[c1.second], nvl[c2.second]) + 1);
}

int main(){
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	dfs(0,0);
	for(int i = 0; i < q; i++){
		int a, b, c, d, ans = 0;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		a--, b--, c--, d--;
		vector<pair<int,int> > x = get(a,b), y = get(c,d);
		for(int j = 0; j < (int)x.size(); j++)
			for(int k = 0; k < (int)y.size(); k++)
				ans += query(x[j], y[k]);
		printf("%d\n", ans);
	}
}

