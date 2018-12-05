#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1e6 + 1;

bool notPrime[MAXN];
int sz, primes[MAXN];

int verify(ll k){
	int cnt = 0;
	for(int i = 0; i < sz; i++){
		if(k % primes[i] == 0){
			k /= primes[i];
			cnt++;
			if(k % primes[i] == 0)
				return 0;
		}
	}
	if(k > 1)
		cnt++;
	if(cnt < 2)
		return 0;
	return 1;
}

int main(){
	for(int i = 2; i < MAXN; i++){
		if(!notPrime[i]){
			primes[sz++] = i;
			for(ll j = (ll)i * i; j < MAXN; j += i)
				notPrime[j] = true;
		}
	}
	ll n;
	scanf("%lld", &n);
	int ans = 0;
	for(ll i = 1; i * i <= n; i++){
		if(n % i != 0)
			continue;
		ans += verify(i);
		if(i * i < n)
			ans += verify(n / i);
	}
	printf("%d\n", ans);
}
