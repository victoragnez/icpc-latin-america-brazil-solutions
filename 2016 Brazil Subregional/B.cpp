#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4 + 1;

struct Node{
	int qt, l, r;
	Node() : qt(0), l(0), r(0){ }
}st[MAXN * 20];
int ptr = 1;

int upd(int node, int l, int r, int p, int v){
	if(p < l || r < p)
		return node;
	if(l == r){
		st[ptr].qt = st[node].qt + v;
		st[ptr].l = st[node].l;
		st[ptr].r = st[node].r;
	 	return ptr++;
	}
	int mid = (l + r) >> 1, fe, fd;

	fe = upd(st[node].l, l, mid, p, v);
	fd = upd(st[node].r, mid + 1, r, p, v);

	st[ptr].qt = st[fe].qt + st[fd].qt;
	st[ptr].l = fe;
	st[ptr].r = fd;
	return ptr++;
}

pair<int, int> query_qt(int a, int b, int l, int r, int k){
	if(l == r)
		return make_pair(st[b].qt - st[a].qt, st[b].qt - st[a].qt);
	int mid = (l + r) >> 1;
	int t_left = st[st[b].l].qt - st[st[a].l].qt;
	if(t_left >= k)
		return query_qt(st[a].l, st[b].l, l, mid, k);
	pair<int, int> ret = query_qt(st[a].r, st[b].r, mid + 1, r, k - t_left);
	ret.first += t_left;
	return ret;
}

int query_pos(int a, int b, int l, int r, int k){
	if(l == r)
		return l;
	int mid = (l + r) >> 1;
	int t_left = st[st[b].l].qt - st[st[a].l].qt;
	if(t_left >= k)
		return query_pos(st[a].l, st[b].l, l, mid, k);
	return query_pos(st[a].r, st[b].r, mid + 1, r, k - t_left);
}

int n, q;
int prx[MAXN], vis[MAXN], vet[MAXN], root[MAXN];

int dfs(int v){
	if(vis[v] == 1)
		return vet[v];
	if(vis[v] == 2){
		int mn = v, u = prx[v];
		while(u != v){
			mn = min(mn, u);
			u = prx[u];
		}
		u = v;
		do{
			vis[u] = 1;
			vet[u] = mn;
			u = prx[u];
		} while(u != v);
		return vet[v];
	}
	vis[v] = 2;
	vet[v] = min(v, dfs(prx[v]));
	vis[v] = 1;
	return vet[v];
}

int main(){
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++)
		scanf("%d", prx + i);
	for(int i = 1; i <= n; i++)
		root[i] = upd(root[i - 1], 1, n, dfs(i), 1);

	for(int i = 0; i < q; i++){
		int l, r;
		scanf("%d%d", &l, &r);
		int len = r - l + 1;
		pair<int, int> pa = query_qt(root[l - 1], root[r], 1, n, (len + 1) / 2);
		int op1 = pa.first - pa.second, op2 = pa.first, best;
		if(len - 2 * op1 <= 2 * op2 - len)
			best = op1;
		else
			best = op2;
		int ans = query_pos(root[l - 1], root[r], 1, n, best);
		printf("%d\n", ans);
	}
}

