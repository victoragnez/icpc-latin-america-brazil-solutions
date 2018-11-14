#include <bits/stdc++.h>
using namespace std;

bitset<1001> state, vet[1001], cc;
int n, m;

int main(){
	scanf("%d%d", &n, &m);
	int l;
	scanf("%d", &l);
	for(int i = 0; i < l; i++){
		int p;
		scanf("%d", &p);
		state.set(p-1);
	}
	for(int i = 0; i < n; i++){
		int k;
		scanf("%d", &k);
		for(int j = 0; j < k; j++){
			int v;
			scanf("%d", &v);
			vet[i].set(v-1);
		}
	}
	cc.reset();
	for(int i = 0; i < 2*n; i++){
		cc ^= vet[i%n];
		if(cc == state){
			printf("%d\n", i+1);
			return 0;
		}
	}
	puts("-1");
}
