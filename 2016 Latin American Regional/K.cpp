#include<bits/stdc++.h>
using namespace std;

typedef int flow_t;
flow_t inf = 1e9;
namespace maxFlow{
	const int N = 103, M = 8 * N;
	int y[M], nxt[M], cnt[N], fst[N], c[N], pre[N], q[N], dist[N];
	flow_t f[M];
	int S, T, tot, n;
	
	void init(int s, int t, int _n){
		tot = 0;
		S = s;
		T = t;
		n = _n;
		
		for(int i = 0; i < n; i++)
			fst[i] = -1;
	}
	
	void add(int u, int v, flow_t c1, flow_t c2 = 0){
		y[tot] = v;
		f[tot] = c1;
		nxt[tot] = fst[u];
		fst[u] = tot;
		tot++;
		
		y[tot] = u;
		f[tot] = c2;
		nxt[tot] = fst[v];
		fst[v] = tot;
		tot++;
	}
	
	flow_t solve(){
		int t = 1;
		for(int i = 0; i < n; i++){
			cnt[i] = 0;
			dist[i] = n;
			c[i] = fst[i];
		}
		
		q[0] = T;
		dist[T] = 0;
		pre[S] = -1;
		
		for(int i = 0; i < t; i++){
			int u = q[i];
			for(int j = fst[u]; j != -1; j = nxt[j]){
				if(dist[y[j]] > dist[u] + 1 && f[j^1] > 0){ 
					q[t++] = y[j];
					dist[y[j]] = dist[u] + 1;
				}
			}
		}
		
		flow_t flow = 0;
		
		int u = S;
		for(int i = 0; i < n; i++)
			cnt[dist[i]]++;
		
		while(dist[S] <= n){
			while(c[u] != -1 && (!f[c[u]] || dist[y[c[u]]]+1 != dist[u]))
				c[u] = nxt[c[u]];
				
			if(c[u] != -1){
				pre[y[c[u]]] = c[u]^1;
				u = y[c[u]];
				
				if(u == T){
					flow_t minf = inf;
					for(int p = pre[T]; p != -1; p = pre[y[p]])
						minf = min(minf,f[p^1]);
						
					for(int p = pre[T]; p != -1; p = pre[y[p]]){
						f[p^1] -= minf;
						f[p] += minf;
					}
					flow += minf;
					u = S;
				}
			}
			 
			else{
				if(--cnt[dist[u]] == 0)
					break;
				int mind = n;
				c[u] = fst[u];
				for(int j = fst[u]; j != -1; j = nxt[j]){
					if(f[j] > 0 && dist[y[j]] < mind){
						mind = dist[y[j]];
						c[u] = j;
					}
				}
					
				dist[u] = mind + 1;
				cnt[dist[u]]++;
				if(u != S)
					u = y[pre[u]];
			}
		}
		return flow;
	}
}

int n, ans;
int opt1[50], opt2[50];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d %d", opt1 + i, opt2 + i);
		opt1[i]--;
		opt2[i]--;
	}
	
	for(int i = 0; i < n; i++){
		int qt = 0;
		for(int j = 0; j < n; j++)
			if(opt1[j] == i || opt2[j] == i)
				qt++;
		
		if(qt < 2){
			ans++;
			continue;
		}
		
		int S = 2 * n, T = S + 1, N = T + 1;
		maxFlow::init(S, T, N);
		for(int j = 0; j < n; j++){
			if(i == j)
				continue;
			
			if(opt1[i] == j || opt2[i] == j)
				maxFlow::add(n + j, T, qt - 2);
			else
				maxFlow::add(n + j, T, qt - 1);
			
			if(opt1[j] == i || opt2[j] == i)
				continue;

			maxFlow::add(S, j, 1);
			maxFlow::add(j, n + opt1[j], 1);
			maxFlow::add(j, n + opt2[j], 1);
		}
		int flow = maxFlow::solve();
		ans += (flow < n - 1 - qt);
	}
	printf("%d\n", ans);
}

