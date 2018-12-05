#include<bits/stdc++.h>
using namespace std;

int main(){
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	int v1 = 2 * b + 4 * c;
	int v2 = 2 * a + 2 * c;
	int v3 = 4 * a + 2 * b;
	printf("%d\n", min(v1, min(v2, v3)));
}
