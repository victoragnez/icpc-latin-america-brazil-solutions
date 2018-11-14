#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e4 + 1;
typedef long long ll;

typedef ll flow_t;
flow_t inf = 1e15;
namespace maxFlow{
	const int N = 2000 + 5, M = 2*(N + MAXN);
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
				if(dist[y[j]] > dist[u]+1 && f[j^1] > 0){ 
					q[t++] = y[j];
					dist[y[j]] = dist[u]+1;
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
						minf=min(minf,f[p^1]);
						
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
						mind=dist[y[j]];
						c[u] = j;
					}
				}
					
				dist[u]=mind+1;
				cnt[dist[u]]++;
				if(u != S)
					u = y[pre[u]];
			}
		}
		return flow;
	}
}

int a, b, m, va[1001], vb[1001];
tuple<int, int, int> ar[MAXN];

ll sum;

bool binarySearch(int k){
	int S = a+b, T = S+1, n = T+1;
	
	maxFlow::init(S, T, n);
	for(int i = 0; i < a; i++)
		maxFlow::add(i, T, va[i]);
		
	for(int i = 0; i < b; i++)
		maxFlow::add(S, a + i, vb[i]);
		
	for(int i = 0; i <= k; i++)
		maxFlow::add(a + get<2>(ar[i]), get<1>(ar[i]), (flow_t)1e10);
		
	ll val = maxFlow::solve();
	return val == sum;
}

int main(){
	scanf("%d%d%d", &a, &b, &m);
	for(int i = 0; i < a; i++)
		scanf("%d", va+i), sum += va[i];
	for(int i = 0; i < b; i++)
		scanf("%d", vb+i);
	for(int i = 0; i < m; i++){
		int v1, v2, v3;
		scanf("%d%d%d", &v1, &v2, &v3);
		v1--;
		v2--;
		ar[i] = make_tuple(v3, v1, v2);
	}
	sort(ar,ar+m);
	
	int l = 0, r = m-1, ans = -1;
	while(l <= r){
		int mid = (l+r)>>1;
		if(binarySearch(mid)){
			ans = get<0>(ar[mid]);
			r = mid-1;
		}
		else{
			l = mid+1;
		}
	}
	
	printf("%d\n", ans);
}

