#include <bits/stdc++.h>
using namespace std;
const int MAXN = 800 + 1;
const int inf = 1e9;

vector<int> adj[MAXN];
int par[MAXN], dist[MAXN];

bool bsf(int n){
	queue<int> q;
	for(int i = 1; i <= n; i++){
		if(par[i] == 0){
			dist[i] = 0;
			q.push(i);
		}
		else dist[i] = inf;
	}
	dist[0] = inf;
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(int i = 0; i < (int)adj[v].size(); i++){
			int u = adj[v][i];
			if(dist[par[u]] == inf){
				dist[par[u]] = dist[v] + 1;
				q.push(par[u]);
			}
		}
	}
	return (dist[0] != inf);
}

bool dfs(int v){
	if(!v)
		return 1;
	for(int i = 0; i < (int)adj[v].size(); i++){
		int u = adj[v][i];
		if(dist[par[u]] == dist[v] + 1 && dfs(par[u])){
			par[u] = v;
			par[v] = u;
			return 1;
		}
	}
	dist[v] = inf;
	return 0;
}

int hopcroftKarp(int n){
	for(int i = 1; i <= n; i++)
		par[i] = 0;
	int matching = 0;
	while(bsf(n))
		for(int i = 1; i <= n; i++)
			if(!par[i] && dfs(i))
				matching++;
	return matching;
}

int n, m, ptr, mx[] = {-1, 1, 0, 0}, my[] = {0, 0, -1, 1};
vector<int> vertices[20][20];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++){ 
		for(int j = 0; j < m; j++){
			char c;
			scanf(" %c", &c);
			vertices[i][j].emplace_back(++ptr);
			if(c=='-')
				vertices[i][j].emplace_back(++ptr);
		}
	}
	if(ptr & 1){
		puts("N");
		return 0;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			for(int k = 0; k < 4; k++){
				int pi = i + mx[k], pj = j + my[k];
				if(pi >= n || pj >= m || pi < 0 || pj < 0)
					continue;
				for(int a = 0; a < (int)vertices[i][j].size(); a++)
					for(int b = 0; b < (int)vertices[pi][pj].size(); b++)
						adj[vertices[i][j][a]].emplace_back(vertices[pi][pj][b]);
			}
		}
	}
	if(hopcroftKarp(ptr) == ptr/2)
		puts("Y");
	else
		puts("N");
}

