#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 1;
int n, t, a, ac, x, y;
int first[MAXN], vet[30];

int next(int v){
	int ret = (v >> 1);
	for(int i = 0; i < t; i++)
		if((v & (1 << vet[i])) != 0)
			ret ^= (1 << (n - 1));
	return ret;
}

int main(){
	scanf("%d%d%d%d%d", &n, &t, &a, &x, &y);
	for(int i = 0; i < t; i++)
		scanf("%d", vet + i);
	ac = a % x;
	const int inf = 1e9;
	for(int i = 1; i < x; i++)
		first[i] = inf;
	first[0] = -1;
	for(int i = 0; ; i++){
		if(first[ac] == inf)
			first[ac] = i;
		if(first[ac] != inf && i - first[ac] >= y){
			printf("%d %d\n", first[ac] + 1, i);
			return 0;
		}
		a = next(a);
		ac = (ac + a) % x;
	}
}

