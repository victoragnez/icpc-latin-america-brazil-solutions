#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e4 + 1;
int n, vet[MAXN];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", vet + i);
		vet[i] = min(vet[i], (i ? vet[i - 1] : 0) + 1);
	}
	for(int i = n - 1; i >= 0; i--)
		vet[i] = min(vet[i], vet[i + 1] + 1);
	printf("%d\n", *max_element(vet, vet + n));
}

