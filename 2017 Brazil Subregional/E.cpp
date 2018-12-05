#include<bits/stdc++.h>
using namespace std;

int n;
string names[] = {"do", "do#", "re", "re#", "mi", "fa", "fa#", "sol", "sol#", "la", "la#", "si"};
int delta[] = {2, 2, 1, 2, 2, 2, 1};
bool isUsed[12], inScale[12];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int v;
		scanf("%d", &v);
		isUsed[(v - 1) % 12] = true;
	}
	for(int i = 0; i < 12; i++){
		memset(inScale, false, sizeof(inScale));
		int cur = i;
		inScale[cur] = true;
		for(int j = 0; j < 7; j++){
			cur = (cur + delta[j]) % 12;
			inScale[cur] = true;
		}
		bool ok = true;
		for(int j = 0; j < 12; j++){
			if(isUsed[j] && !inScale[j]){
				ok = false;
				break;
			}
		}
		if(ok){
			printf("%s\n", names[i].c_str());
			return 0;
		}
	}
	puts("desafinado");
}
