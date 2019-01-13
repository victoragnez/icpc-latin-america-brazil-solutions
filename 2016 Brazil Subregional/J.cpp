#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
const int MAXN = 1e5 + 1;
const double EPS = 1e-9, inf = 1e20;

int cmp(double x, double y = 0, double tol = EPS){
	return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int n, ord[MAXN], nxt[MAXN];
pii a[MAXN], b[MAXN];
pdd va[MAXN], vb[MAXN];
bool removed[MAXN];

void solve(pii * vet, pdd * res){
	memset(removed, 0, sizeof(removed));
	auto get = [&](int id, double t){
		return vet[id].first + vet[id].second * t;
	};
	auto intersect = [&](int i, int j){
		return -(vet[i].first - vet[j].first) / (double)(vet[i].second - vet[j].second);
	};
	iota(ord, ord + n, 0);
	sort(ord, ord + n, [&](int i, int j){
		return vet[i].first > vet[j].first;
	});
	int t = 0;
	set<pair<double, int> > q;
	for(int i = 0; i < n; i++){
		if(i + 1 < n && vet[ord[i]] == vet[ord[i + 1]])
			i++;
		else if(t > 0 && vet[ord[t - 1]].second >= vet[ord[i]].second)
			continue;
		else{
			if(t > 0){
				q.insert(make_pair(intersect(ord[t - 1], ord[i]), ord[i]));
				nxt[ord[i]] = ord[t - 1];
			}
			ord[t++] = ord[i];
		}
	}
	nxt[ord[0]] = -1;
	res[ord[0]] = make_pair(0., inf);
	while(!q.empty()){
		double cur = q.begin()->first;
		int v = q.begin()->second;
		q.erase(q.begin());
		if(removed[v] || nxt[v] == -1)
			continue;
		int u = nxt[v];
		if(!cmp(get(v, cur), get(u, cur))){
			removed[u] = true;
			if(nxt[u] == -1){
				res[u].second = cur;
				res[v] = make_pair(cur, inf);
			}
			nxt[v] = nxt[u];
		}
		if(nxt[v] != -1)
			q.insert(make_pair(intersect(nxt[v], v), v));
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d%d%d%d", &a[i].first, &a[i].second, &b[i].first, &b[i].second);
		b[i].first = -b[i].first;
		b[i].second = -b[i].second;
	}
	solve(a, va);
	solve(b, vb);
	int ans = 0;
	for(int i = 0; i < n; i++){
		pdd res;
		res.first = max(va[i].first, vb[i].first);
		res.second = min(va[i].second, vb[i].second);
		if(cmp(res.first, res.second) < 0)
			ans++;
	}
	printf("%d\n", ans);
}

