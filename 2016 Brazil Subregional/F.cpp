#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e4 + 1;
int n, m, l[MAXN], c[MAXN], r[MAXN];

int dfs(int v, int & maxv){
	if(!v){
		return 0;
	}
	int ret = dfs(c[v], maxv) + 1;
	maxv = max(maxv, ret);
	dfs(l[v], maxv);
	dfs(r[v], maxv);
	return ret;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int id, a, b;
		scanf("%d%d%d", &id, &a, &b);
		l[id] = a;
		c[id] = b;
	}
	scanf("%d", &m);
	for(int i = 0; i < m; i++){
		int id, a, b;
		scanf("%d%d%d", &id, &a, &b);
		if(a != 0)
			c[id + n] = a + n;
		if(b != 0)
			r[id + n] = b + n;
	}
	int nroot, nmax = 0;
	nroot = dfs(1, nmax);
	int mroot, mmax = 0;
	mroot = dfs(n + 1, mmax);
	printf("%d\n", n + m - max(min(nroot, mmax), min(mroot, nmax)));
}

