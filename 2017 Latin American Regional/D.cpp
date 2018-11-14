#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;

set<tuple<int, int, int> > seg;
int L, C, n, cnt[MAXN];

bool inter(pair<int, int> a, pair<int, int> b){
	return !(a.second < b.first || b.second < a.first);
}

void rm(tuple<int, int, int> s, pair<int, int> cur){
	int tl, tr, c;
	
	tie(tl, tr, c) = s;
	seg.erase(s);
	cnt[c] -= tr - tl + 1;
	
	if(tl <= cur.first && cur.second <= tr){
		if(tl < cur.first){
			seg.insert(make_tuple(tl, cur.first - 1, c));
			cnt[c] += cur.first - tl;
		}
		if(cur.second < tr){
			seg.insert(make_tuple(cur.second + 1, tr, c));
			cnt[c] += tr - cur.second;
		}
		return;
	}
	
	if(cur.first <= tl && tl <= cur.second)
		tl = cur.second + 1;
	if(cur.first <= tr && tr <= cur.second)
		tr = cur.first - 1;
	
	if(tl <= tr){
		seg.insert(make_tuple(tl, tr, c));
		cnt[c] += tr - tl + 1;
	}
}

int main(){
	scanf("%d%d%d", &L, &C, &n);
	seg.insert(make_tuple(0, L-1, 1));
	cnt[1] = L;
	while(n--){
		int p, x, a, b;
		scanf("%d%d%d%d", &p, &x, &a, &b);
		int s = cnt[p];
		int l = (int) ((a + (long long)s * s) % L);
		int r = (int) ((a + (long long)(s + b) * (s + b)) % L);
		if(r < l)
			swap(l,r);
		
		while(true){
			auto it = seg.lower_bound(make_tuple(l, -1, -1));
			if(it == seg.end() || !inter(make_pair(get<0>(*it), get<1>(*it)), make_pair(l, r)))
				break;
			rm(*it, make_pair(l, r));
		}
		
		auto it = seg.lower_bound(make_tuple(l, -1, -1));
		
		if(it != seg.begin()){
			it--;
			if(inter(make_pair(get<0>(*it), get<1>(*it)), make_pair(l, r)))
				rm(*it, make_pair(l, r));
		}
		
		cnt[x] += r-l+1;
		seg.insert(make_tuple(l, r, x));
	}
	printf("%d\n", *max_element(cnt + 1, cnt + C + 1));
}

