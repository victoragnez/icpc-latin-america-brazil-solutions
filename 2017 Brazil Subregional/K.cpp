#include<bits/stdc++.h>
using namespace std;

const int mod = 10000;

struct mat{
	int m[2][2];
	
	mat(int a, int b, int c, int d){
		m[0][0] = a;
		m[0][1] = b;
		m[1][0] = c;
		m[1][1] = d;
	}
	
	int * operator[](int i){
		return m[i];
	}
};

//Matrix multiplication
mat mul(mat a, mat b){
	mat c(0, 0, 0, 0);
	int id[] = {0, 1};
	for(int i : id)
		for(int j : id)
			for(int k : id)
				c[i][j] = (c[i][j] + a[i][k] * b[k][j])%mod;
	return c;
}

int main(){
	int a, b, n, k;
	scanf("%d%d%d%d", &a, &b, &n, &k);
	int odd = n & 1;
	mat aux(1, 0, 0, 1), base(a, b, 1, a);
	
	//Exponentiation by squaring
	while(n > 0){
		if(n & 1)
			aux = mul(aux, base);
		base = mul(base, base);
		n >>= 1;
	}
	
	int ans = (2 * aux[0][0]) % mod;
	if(a * a > b || (!odd && a * a < b))
		ans = (ans + mod - 1) % mod;
	while(--k > 0)
		ans /= 10;
	printf("%d\n", ans % 10);
}
