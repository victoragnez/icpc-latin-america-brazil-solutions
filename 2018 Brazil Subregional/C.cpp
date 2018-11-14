#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 1;

int aux[MAXN];

void compress(int * v, int n){
	for(int i = 0; i < n; i++)
		aux[i] = v[i];
	sort(aux,aux+n);
	for(int i = 0; i < n; i++)
		v[i] = (int)(lower_bound(aux, aux+n, v[i]) - aux);
}

int fenwick[MAXN];

void upd(int p, int v){
	for(p++; p < MAXN; p += p&-p)
		fenwick[p] += v;
}

int query(int p){
	int ret = 0;
	for(p++; p > 0; p -= p&-p)
		ret += fenwick[p];
	return ret;
}

pair<int, int> vet[MAXN];

ll count(int * u, int * v, int n){
	memset(fenwick, 0, sizeof(fenwick));
	for(int i = 0; i < n; i++)
		vet[i] = make_pair(u[i],v[i]);
	sort(vet,vet+n);
	
	ll ret = 0;
	for(int i = 0; i < n; i++){
		ret += i-query(vet[i].second);
		upd(vet[i].second,1);
	}
	return ret;
}

int n, m, va[MAXN], vb[MAXN];

int main(){
	
	scanf("%*d%*d");
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++)
		scanf("%d%d", va+i, vb+i);
	
	compress(va,n);
	compress(vb,n);
	
	ll ans = count(va, vb, n) + (ll)(m+1)*(n+1);
	
	for(int i = 0; i < m; i++)
		scanf("%d%d", va+i, vb+i);
	
	compress(va, m);
	compress(vb, m);
	
	ans += count(va, vb, m);
	
	printf("%lld\n", ans);
}

