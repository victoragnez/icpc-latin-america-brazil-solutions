#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 1;

ll n, m, mobius[MAXN];
const ll mod = 1e9 + 7;
bool notPrime[MAXN];

ll solve(ll k, int strict){
	ll ret = 0;
	for(ll d = 1; d <= n; d++){
		ll sd = 0;
		for(ll i = 1; i*d < n; i++){
			if(i*d > k - strict)
				break;
			
			ll qt = min((ll)(sqrtl(k*k-(i*d)*(i*d))/d), m/d);
			ll a1 = m - d;
			
			while(m > (qt+1)*d && k*k - strict >= (i*d)*(i*d) + (qt+1)*d*(qt+1)*d)
				qt++;
			while(!(m > qt*d && k*k - strict >= (i*d)*(i*d) + qt*d*qt*d))
				qt--;
			
			if(qt <= 0)
				continue;
				
			ll an = m - qt*d;
			ll cur = (a1 + an)*qt/2;
			cur %= mod;
			sd += (n-d*i) * cur;
			sd %= mod;
		}
		ret += sd*mobius[d] + mod;
		ret %= mod;
	}
	return (2*ret)%mod;
}

int main(){
	for(int i = 0; i < MAXN; i++)
		mobius[i] = 1;
	for(int i = 2; i < MAXN; i++){
		if(!notPrime[i]){
			mobius[i] = -mobius[i];
			for(int j = i+i; j < MAXN; j += i){
				if(j % ((ll)i*i) == 0)
					mobius[j] = 0;
				mobius[j] = -mobius[j];
				notPrime[j] = 1;
			}
		}
	}
	int l, r;
	scanf("%lld%lld%d%d", &n, &m, &l, &r);
	ll extra = 0;
	if(l == 1)
		extra = (n*(m-1) + (n-1)*m)%mod;
	printf("%lld\n", (solve(r, 0) - solve(l, 1) + extra + mod)%mod);
}

