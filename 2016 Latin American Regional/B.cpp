#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;

int n, m, a, b, deg[MAXN];
vector<int> adj[MAXN];
set<pair<int, int> > degs;
bool removed[MAXN];

int main(){
	scanf("%d%d%d%d", &n, &m, &a, &b);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	for(int i = 0; i < n; i++){
		deg[i] = (int)adj[i].size();
		degs.insert(make_pair(deg[i], i));
	}
	int ans = n;
	while(ans > 0){
		int v = -1;
		if(degs.begin()->first < a)
			v = degs.begin()->second;
		else if(ans - 1 - degs.rbegin()->first < b)
			v = degs.rbegin()->second;
		else
			break;
			
		degs.erase(make_pair(deg[v], v));
		
		for(int u : adj[v]){
			if(!removed[u]){
				degs.erase(make_pair(deg[u], u));
				deg[u]--;
				degs.insert(make_pair(deg[u], u));
			}
		}
		removed[v] = true;
		ans--;
	}
	
	printf("%d\n", ans);
}
