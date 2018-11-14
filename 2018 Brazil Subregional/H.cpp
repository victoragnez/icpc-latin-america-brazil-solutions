#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;
const int LOGN = 18;

vector<int> adj[MAXN];
char base[MAXN];
int ptr;
int cnum, cid[MAXN], chead[MAXN], posb[MAXN], nodeb[MAXN];
int nvl[MAXN], anc[MAXN][LOGN], tam[MAXN];

char pat[101], tex[MAXN];
int patLen;

int F[MAXN];

void kmpPreprocess(){
	int i = 0, j = -1;
	F[0] = -1;
	while(i < patLen){
		while(j >= 0 && pat[i] != pat[j])
			j = F[j];
		F[++i] = ++j;
	}
}

pair<int, int> adv(int j, char c){
	while(j >= 0 && c != pat[j])
		j = F[j];
	j++;
	int qt = 0;
	if(j == patLen){
		qt++;
		j = F[j];
	}
	return make_pair(j, qt);
}

struct Node{
	pair<int, int> res[101];
	Node(){
		for(int i = 0; i < patLen; i++)
			res[i] = make_pair(i,0);
	}
	void reset(char c){
		for(int i = 0; i < patLen; i++)
			res[i] = adv(i, c);
	}
	pair<int, int> & operator[](int id){
		return res[id];
	}
} st1[MAXN<<2], st2[MAXN<<2];

Node merge(Node a, Node b){
	Node c;
	for(int i = 0; i < patLen; i++)
		c[i] = make_pair(b[a[i].first].first, a[i].second + b[a[i].first].second);
	return c;
}

void build_tree(int b, int l, int r){
	if(l==r){
		st1[b].reset(base[l]);
		st2[b].reset(base[l]);
		return;
	}
	int fe = b<<1, fd = fe|1, mid = (l+r)>>1;
	build_tree(fe, l, mid);
	build_tree(fd, mid+1, r);
	st1[b] = merge(st1[fe], st1[fd]);
	st2[b] = merge(st2[fd], st2[fe]);
}

void upd_tree(int b, int l, int r, int p, char v){
	if(r < p || p < l)
		return;
	if(l == r){
		st1[b].reset(v);
		st2[b].reset(v);
		return;
	}
	int fe = b<<1, fd = fe|1, mid = (l+r)>>1;
	upd_tree(fe, l, mid, p, v);
	upd_tree(fd, mid+1, r, p, v);
	st1[b] = merge(st1[fe], st1[fd]);
	st2[b] = merge(st2[fd], st2[fe]);
}

Node query_tree(int b, int l, int r, int x, int y, bool inve){
	if(y < l || r < x)
		return Node();
	if(x <= l && r <= y){
		if(inve)
			return st2[b];
		return st1[b];
	}
	int fe = b<<1, fd = fe|1, mid = (l+r)>>1;
	if(inve)
		return merge(query_tree(fd, mid+1, r, x, y, inve), query_tree(fe, l, mid, x, y, inve));
	return merge(query_tree(fe, l, mid, x, y, inve), query_tree(fd, mid+1, r, x, y, inve));
}

Node query_up(int u, int v, bool inve){
	int cu, cv = cid[v];
	Node ret;
	while(true){
		cu = cid[u];
		if(cu == cv){
			if(inve)
				ret = merge(ret, query_tree(1, 0, ptr-1, posb[v], posb[u], inve));
			else
				ret = merge(query_tree(1, 0, ptr-1, posb[v], posb[u], inve), ret);
			break;
		}
		if(inve)
			ret = merge(ret, query_tree(1, 0, ptr-1, posb[chead[cu]], posb[u], inve));
		else
			ret = merge(query_tree(1, 0, ptr-1, posb[chead[cu]], posb[u], inve), ret);
		u = chead[cu];
		u = anc[u][0];
	}
	return ret;
}

int moveUp(int v, int diff){
	for(int i = 0; i < LOGN; i++)
		if(diff & (1<<i))
			v = anc[v][i];
	return v;
}

int LCA(int u, int v){
	if(nvl[u] < nvl[v])
		swap(u,v);
	u = moveUp(u, nvl[u] - nvl[v]);
	if(u == v)
		return u;
	for(int i = LOGN - 1; i >= 0; i--){
		if(anc[u][i] != anc[v][i]){
			u = anc[u][i];
			v = anc[v][i];
		}
	}
	return anc[u][0];
}

int query(int u, int v){
	bool swaped = 0;
	if(nvl[u] < nvl[v]){
		swap(u, v);
		swaped = 1;
	}
	int lca = LCA(u, v);
	if(lca == v)
		return query_up(u, v, !swaped)[0].second;
	if(swaped)
		swap(u,v);
	int aux = moveUp(u, nvl[u] - nvl[lca] - 1);
	return merge(query_up(u, aux, 1), query_up(v, lca, 0))[0].second;
}

void HLD(int v, int pr){
	if(chead[cnum] == -1)
		chead[cnum] = v;
	
	cid[v] = cnum;
	posb[v] = ptr;
	nodeb[ptr] = v;
	base[ptr++] = tex[v];
	
	int best = -1;
	for(int i = 0; i < (int)adj[v].size(); i++)
		if(adj[v][i] != pr && (best == -1 || tam[best] < tam[adj[v][i]]))
			best = adj[v][i];

	if(best != -1){
		HLD(best, v);
	}

	for(int i = 0; i < (int)adj[v].size(); i++){
		if(adj[v][i] != pr && adj[v][i] != best){
			cnum++;
			HLD(adj[v][i], v);
		}
	}
}

void dfs(int v, int pr){
	tam[v] = 1;
	for(int i = 0; i < (int)adj[v].size(); i++){
		if(adj[v][i] != pr){
			int u = adj[v][i];
			nvl[u] = nvl[v] + 1;
			anc[u][0] = v;
			for(int j = 1; j < LOGN; j++)
				anc[u][j] = anc[anc[u][j-1]][j-1];
			dfs(u, v);
			tam[v] += tam[u];
		}
	}
}

int n, q;
char aux[MAXN];

int main(){
	memset(chead, -1, sizeof(chead));
	scanf("%d%d", &n, &q);
	scanf("%s", pat);
	patLen = (int)strlen(pat);
	scanf("%s", tex);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	
	kmpPreprocess();
	dfs(0, 0);
	HLD(0, 0);
	build_tree(1, 0, ptr-1);
	
	
	while(q--){
		int tp;
		scanf("%d", &tp);
		if(tp==1){
			int u, v;
			scanf("%d%d", &u, &v);
			u--, v--;
			printf("%d\n", query(u,v));
		}
		else{
			int v;
			char c;
			scanf("%d %c", &v, &c);
			v--;
			upd_tree(1, 0, ptr-1, posb[v], c);
		}
	}
}

