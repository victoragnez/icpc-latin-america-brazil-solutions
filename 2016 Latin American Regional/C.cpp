#include <bits/stdc++.h>
using namespace std;

struct my_hash{
	inline size_t operator ()(const pair<int, int> & a) const {
		return (a.first << 6) ^ (a.first >> 2) ^ 2038074743 ^ a.second;
	}
};

const int MAXN = 1000 + 1;
const int mod = 1e9 + 7;
unordered_map<pair<int, int>, int, my_hash> points, ori;
int n, x[MAXN], y[MAXN], bin[MAXN][MAXN], ans[MAXN];

int main(){
	bin[0][0] = 1;
	for(int i = 1; i < MAXN; i++){
		bin[i][0] = 1;
		for(int j = 1; j <= i; j++)
			bin[i][j] = (bin[i-1][j] + bin[i-1][j-1])%mod;
	}
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d %d", &x[i], &y[i]);
		x[i] *= 2;
		y[i] *= 2;
		ori[make_pair(x[i], y[i])] = 1;
		for(int j = 0; j < i; j++){
			int mx = (x[i] + x[j]) / 2;
			int my = (y[i] + y[j]) / 2;
			points[make_pair(mx, my)]++;
		}
	}
	for(auto it : points)
		for(int j = 1; j <= it.second; j++)
			ans[2*j] = (ans[2*j] + bin[it.second][j])%mod;

	for(auto it : ori)
		for(int j = 0; j <= points[it.first]; j++)
			ans[(2*j) | 1] = (ans[(2*j) | 1] + bin[points[it.first]][j])%mod;

	for(int i = 1; i <= n; i++)
		printf("%d%c", ans[i], i==n?'\n':' ');
}

