#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 1;

map<pair<int,int>, ll> cnt;
int n, va[MAXN], vb[MAXN], vc[MAXN], auxa[MAXN], auxb[MAXN];
ll bit[MAXN];
struct event{
	int x, y;
	ll c;
};
vector<event> vet;

void upd(int p, ll v){
	for(p++; p > 0; p -= p&-p)
		bit[p] = max(bit[p], v);
}

ll query(int p){
	ll ret = 0;
	for(p++; p < MAXN; p += p&-p)
		ret = max(ret, bit[p]);
	return ret;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d%d%d", va+i, vb+i, vc+i);
		auxa[i] = va[i];
		auxb[i] = vb[i];
	}

	sort(auxa,auxa+n);
	sort(auxb,auxb+n);
	for(int i = 0; i < n; i++){
		va[i] = (int) (lower_bound(auxa, auxa+n, va[i]) - auxa);
		vb[i] = (int) (lower_bound(auxb, auxb+n, vb[i]) - auxb);
		cnt[make_pair(va[i], vb[i])] += vc[i];
	}
	for(auto it : cnt)
		vet.push_back({it.first.first, it.first.second, it.second});
	
	sort(vet.begin(), vet.end(), [](event a, event b){
		if(a.x != b.x)
			return a.x > b.x; 
		return a.y < b.y;
	});
	
	for(int i = 0; i < (int)vet.size(); i++){
		int y = vet[i].y;
		ll c = vet[i].c;
		c += query(y + 1);
		upd(y, c);
	}
	printf("%lld\n", query(0));
}

