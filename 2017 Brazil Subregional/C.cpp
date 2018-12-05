#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 1;
int n, l, lcm = 1;
int primeDiv[MAXN];

int main(){
	for(int i = 2; i < MAXN; i++)
		if(!primeDiv[i])
			for(int j = i; j < MAXN; j += i)
				primeDiv[j] = i;
	scanf("%d%d", &n, &l);
	for(int i = 0; i < n; i++){
		int v;
		scanf("%d", &v);
		lcm /= __gcd(lcm, v);
		lcm *= v;
	}
	int k = l / lcm, ans = 1;
	int gcd = __gcd(k, lcm);
	while(gcd > 1){
		int p = primeDiv[gcd];
		while(k % p == 0){
			k /= p;
			ans *= p;
		}
		while(lcm % p == 0){
			lcm /= p;
			ans *= p;
		}
		while(gcd % p == 0)
			gcd /= p;
	}
	ans *= k;
	printf("%d\n", ans);
}
