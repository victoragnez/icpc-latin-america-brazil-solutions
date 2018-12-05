#include<bits/stdc++.h>
using namespace std;

int n, k, vet[1001];

int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", vet + i);
	sort(vet + 1, vet + n + 1);
	reverse(vet + 1, vet + n + 1);
	while(k < n && vet[k + 1] == vet[k])
		k++;
	printf("%d\n", k);
}
