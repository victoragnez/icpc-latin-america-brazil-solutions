#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

const int B = 16;
ll sum[1 << B], totalSum[1 << B], totalMax[1 << B], totalMin[1 << B], fat[B + 1];
const ll mod = 1e9 + 7;

void apply(ll & v, ll id){
	auto get = [&](int i){
		return (v >> i) & (B - 1);
	};
	auto rm = [&](int i){
		return ((v >> (i + 4)) << i) | (v & ((1ULL << i) - 1));
	};
	for(int i = 0; (1ULL << i) <= v; i += 4){
		if(get(i) == id){
			v = rm(i);
			i -= 4;
		}
	}
}

void build(int id, int mask, vector<ll> & vet){
	if(id == B){
		sum[mask] = accumulate(vet.begin(), vet.end(), 0LL);
		return;
	}
	vector<ll> nxt(vet);
	for(ll & v : nxt)
		apply(v, id);
	build(id + 1, mask, vet);
	build(id + 1, mask | (1 << id), nxt);
}

int main(){
	fat[0] = 1;
	for(int i = 1; i <= B; i++)
		fat[i] = i * fat[i - 1] % mod;

	unsigned n;
	scanf("%x", &n);
	vector<ll> vet;
	for(unsigned i = 0; i < n; i++){
		ll v;
		scanf("%llx", &v);
		vet.emplace_back(v);
	}
	build(0, 0, vet);
	sum[0] = 0;
	for(int i = (1 << B) - 1; i >= 0; i--){
		totalMin[i] = ULONG_MAX;
		for(int j = 0; j < B; j++){
			if(!(i & (1 << j))){
				totalSum[i] = (totalSum[i] + totalSum[i | (1 << j)]) % mod;
				totalMax[i] = max(totalMax[i], totalMax[i | (1 << j)]);
				totalMin[i] = min(totalMin[i], totalMin[i | (1 << j)]);
			}
		}
		if(totalMin[i] == ULONG_MAX)
			totalMin[i] = 0;

		totalMax[i] += sum[i];
		totalMin[i] += sum[i];
		totalSum[i] = (totalSum[i] + (sum[i] % mod) * fat[B - __builtin_popcount(i)]) % mod;
 	}

 	printf("%llx %llx %llx\n", *totalMin, *totalMax, *totalSum);
}
