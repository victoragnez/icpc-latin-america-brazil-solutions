#include<bits/stdc++.h>
using namespace std;

int main(){
	int v[4];
	for(int i = 0; i < 4; i++)
		scanf("%d", v+i);
	sort(v, v + 4);
	printf("%d\n", abs(v[0] + v[3] - v[1] - v[2]));
}
