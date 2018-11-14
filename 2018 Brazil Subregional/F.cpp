#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;

int n, dp[1<<10][1001];
vector<tuple<int, int, int, int> > vet;
vector<int> pr;

int solve(int mask, int cur){
	if(cur == (int)vet.size()){
		if(mask == (1<<n)-1)
			return 0;
		return -inf;
	}
	int & ret = dp[mask][cur];
	if(ret != -1)
		return ret;
	ret = max(solve(mask, cur+1), solve(mask|(1<<get<3>(vet[cur])), pr[cur]) + get<2>(vet[cur]));
	return ret;
}

int main(){
	memset(dp, -1, sizeof(dp));
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int q;
		scanf("%d", &q);
		for(int j = 0; j < q; j++){
			int l, r, o;
			scanf("%d%d%d", &l, &r, &o);
			vet.push_back(make_tuple(l,r,o,i));
		}
	}
	int t = (int)vet.size();
	
	sort(vet.begin(), vet.end());
	
	pr.resize(t, t);
	for(int i = 0; i < t; i++){
		for(int j = i; j < t; j++){
			if(get<1>(vet[i]) <= get<0>(vet[j])){
				pr[i] = j;
				break;
			}
		}
	}
	printf("%d\n", max(solve(0,0),-1));
}

