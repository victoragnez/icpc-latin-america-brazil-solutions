#include <bits/stdc++.h>
using namespace std;
const int MAXN = 15e4 + 1;
typedef long long ll;

struct circle{
	ll x, y, r;
	bool operator<(circle b) const{
		return r < b.r;
	}
} vet[MAXN];

vector<int> adj[MAXN];
int n, ans;

bool inter(circle a, circle b){
	if(a.r < b.r)
		swap(a,b);
	/* if(a.r*a.r - 2*a.r*b.r + b.r*b.r == (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)){
		cerr << "only 1 intersection point:" << endl;
		cerr << a.x << " " << a.y << " " << a.r << endl;
		cerr << b.x << " " << b.y << " " << b.r << endl;
	} */
	return a.r*a.r - 2*a.r*b.r + b.r*b.r <= (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

void dfs(int nv, int v){
	if(!inter(vet[nv],vet[v]))
		return;
	ans += 2;
	if(ans > 2*n){
		puts("greater");
		exit(0);
	}
	for(int u : adj[v])
		dfs(nv, u);
}

void readF(ll & v){
	double x;
	scanf("%lf", &x);
	v = (ll)round(1000*x);
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		readF(vet[i].x);
		readF(vet[i].y);
		readF(vet[i].r);
	}
	sort(vet,vet+n);
	set<int> roots;
	for(int i = 0; i < n; i++){
		for(int id : roots){
			if(inter(vet[i], vet[id]))
				dfs(i, id);
			else
				adj[i].push_back(id);
		}
		for(int id : adj[i])
			roots.erase(id);
		roots.insert(i);
	}
	printf("%d\n", ans);
}

