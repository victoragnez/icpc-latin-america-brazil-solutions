#include <bits/stdc++.h>
using namespace std;

int main(){
	int a, b, c, x, y, z;
	scanf("%d%d%d%d%d%d", &a, &b, &c, &x, &y, &z);
	printf("%d\n", max(0, x - a) + max(0, y - b) + max(0, z - c));
}
