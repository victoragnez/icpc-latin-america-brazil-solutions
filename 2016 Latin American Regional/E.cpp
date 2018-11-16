#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;
 
struct Node{
	int qt, l, r;
	Node() : qt(0), l(0), r(0){ }
}st[MAXN * 3 * 20];
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
 
int query(int a, int b, int l, int r, int k){
	if(l==r)
		return l;
	int mid = (l + r)>>1;
	int t_left = st[st[b].l].qt - st[st[a].l].qt;
	if(t_left >= k)
		return query(st[a].l, st[b].l, l, mid, k);
	return query(st[a].r, st[b].r, mid + 1, r, k - t_left);
}
 
int n, m, vet[MAXN], aux[MAXN], tree[MAXN];
 
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d", vet+i);
		aux[i] = vet[i];
	}
	sort(aux + 1,aux + n + 1);
	for(int i = 1; i <= n; i++){
		vet[i] = (int) (lower_bound(aux + 1, aux + n + 1, vet[i]) - aux);
		tree[i] = upd(tree[i - 1], 1, n, vet[i], 1);
	}
	while(m--){
		char op;
		scanf(" %c", &op);
		if(op == 'Q'){
			int a, b, k;
			scanf("%d%d%d", &a, &b, &k);
			printf("%d\n", aux[query(tree[a - 1], tree[b], 1, n, k)]);
		}else{
			int p;
			scanf("%d", &p);
			tree[p] = upd(tree[p], 1, n, vet[p],-1);
			swap(vet[p], vet[p+1]);
			tree[p] = upd(tree[p], 1, n, vet[p], 1);
		}
	}
}
