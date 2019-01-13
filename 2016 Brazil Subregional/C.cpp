#include<bits/stdc++.h>
using namespace std;

struct conteiner{
	int v[2][4];
	bool operator<(const conteiner & c) const {
		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 4; j++)
				if(v[i][j] != c.v[i][j])
					return v[i][j] < c.v[i][j];
		return false;
	}
	int* operator[](int idx) {
		return v[idx];
	}
	bool operator==(const conteiner & c) const {
		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 4; j++)
				if(v[i][j] != c.v[i][j])
					return false;
		return true;
	}
};

set<pair<int, conteiner> > q;
map<conteiner, int> dist;

conteiner ini, fin;

int main(){
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 4; j++)
			scanf("%d", &ini[i][j]);
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 4; j++)
			scanf("%d", &fin[i][j]);
	dist[ini] = 0;
    q.insert(make_pair(0, ini));
    while(!q.empty()){
		int d = q.begin()->first;
		conteiner v = q.begin()->second;
		q.erase(q.begin());
		if(v == fin){
			printf("%d\n", d);
			return 0;
		}
		for(int i = 0; i < 4; i++){
			conteiner aux = v;
			swap(aux[0][i], aux[1][i]);
			int op = d + aux[0][i] + aux[1][i];
			if(!dist.count(aux) || dist[aux] > op){
				q.erase(make_pair(dist[aux], aux));
				dist[aux] = op;
				q.insert(make_pair(op, aux));
			}
		}
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 3; j++){
				conteiner aux = v;
				swap(aux[i][j], aux[i][j + 1]);
				int op = d + aux[i][j] + aux[i][j + 1];
				if(!dist.count(aux) || dist[aux] > op){
					q.erase(make_pair(dist[aux], aux));
					dist[aux] = op;
					q.insert(make_pair(op, aux));
				}
			}
		}
	}
}

