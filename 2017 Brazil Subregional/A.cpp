#include <bits/stdc++.h>
using namespace std;
 
struct Node{
	int f[9];
	Node(){
		memset(f, 0, sizeof(f));
	}
	int & operator[](int i){
		return f[i];
	}
};
 
Node merge(Node a, Node b){
	Node c;
	for(int i = 0; i < 9; i++)
		c[i] = a[i] + b[i];
	return c;
}
 
const int MAXN = 1e5 + 1;
Node st[MAXN << 2];
int lazy[MAXN << 2];
 
void upd_lazy(int b, int l, int r){
	lazy[b] %= 9;
	if(!lazy[b])
		return;
	Node nxt;
	for(int i = 0; i < 9; i++){
		nxt[lazy[b]] = st[b][i];
		if(lazy[b] == 8)
			lazy[b] = 0;
		else
			lazy[b]++;
	}
	st[b] = nxt;
	if(l < r){
		int fe = b << 1, fd = fe | 1;
		lazy[fe] += lazy[b];
		lazy[fd] += lazy[b];
	}
	lazy[b] = 0;
}
 
void upd(int b, int l, int r, int x, int y, int val){
	upd_lazy(b,l,r);
	if(l > y || r < x) return;
	if(x <= l && r <= y){ 
		lazy[b] = val;
		upd_lazy(b, l, r);
		return;
	}
	int fe = b << 1, fd = fe | 1, m = (l + r) >> 1;
	upd(fe, l, m, x, y, val);
	upd(fd, m + 1, r, x, y, val);
	st[b] = merge(st[fe], st[fd]);
}
 
Node query(int b, int l, int r, int x, int y){
	if(l > y || r < x)
		return Node();
	upd_lazy(b,l,r);
	if(x <= l && r <= y)
		return st[b];
	int fe = b << 1, fd = fe | 1, m = (l + r) >> 1;
	return merge(query(fe, l, m, x, y), query(fd, m + 1, r, x, y));
}
 
void dfs(int b, int l, int r, bool buildTree){
	if(!buildTree)
		upd_lazy(b, l, r);
	if(l == r){
		if(buildTree)
			st[b][1] = 1;
		else
			printf("%d\n", (int) (max_element(st[b].f, st[b].f + 9) - st[b].f));
		return;
	}
	int fe = b << 1, fd = fe | 1, m = (l + r) >> 1;
	dfs(fe, l, m, buildTree);
	dfs(fd, m + 1, r, buildTree);
	if(buildTree)
		st[b] = merge(st[fe], st[fd]);
}
 
int main(){
	int n, q;
	scanf("%d%d", &n, &q);
	dfs(1, 0, n - 1, true);
	for(int i = 0; i < q; i++){
		int l, r;
		scanf("%d%d", &l, &r);
		Node freqs = query(1, 0, n - 1, l, r);
		int v = 0;
		for(int j = 1; j < 9; j++)
			if(freqs[j] >= freqs[v])
				v = j;
		upd(1, 0, n - 1, l, r, v);
	}
	dfs(1, 0, n - 1, false);
}
