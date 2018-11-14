#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;

int n, dx[MAXN], dy[MAXN], valx[MAXN], valy[MAXN], prex[MAXN], sufx[MAXN], prey[MAXN], sufy[MAXN];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n-1; i++)
		scanf("%d", dx+i);
	for(int i = 0; i < n-1; i++)
		scanf("%d", dy+i);
	
	for(int i = 1; i < n; i++){
		valx[i] = valx[i-1]+dx[i-1];
		valy[i] = valy[i-1]+dy[i-1];
	}
	
	int ult = 1e9;
	for(int i = n-1; i >= 0; i--){
		if(dx[i] == 1)
			ult = i;
		sufx[i] = ult;
	}
	ult = 1e9;
	for(int i = n-1; i >= 0; i--){
		if(dy[i] == 1)
			ult = i;
		sufy[i] = ult;
	}
	ult = -1e9;
	for(int i = 0; i < n; i++){
		if(i > 0 && dx[i-1] == 1)
			ult = i;
		prex[i] = ult;
	}
	ult = -1e9;
	for(int i = 0; i < n; i++){
		if(i > 0 && dy[i-1] == 1)
			ult = i;
		prey[i] = ult;
	}
	
	int q;
	scanf("%d", &q);
	while(q--){
		int xa, xb, ya, yb, ans = 1e9;
		scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
		xa--, ya--, xb--, yb--;
		
		if(xa > xb)
			swap(xa,xb);
		if(ya > yb)
			swap(ya,yb);
		
		int v1 = valy[yb] + valx[xb] - valy[ya] - valx[xa];
		if(yb-ya > xb-xa){
			int extra = (yb-ya) - (xb-xa);
			
			if(extra & 1)
				extra ^= 1;

			int d = xa - prex[xa];
			if(d + d <= extra)
				ans = min(ans, (d+d)*5 + extra - d - d);
			
			d = sufx[xb] - xb;
			if(d+d <= extra)
				ans = min(ans, (d+d)*5 + extra - d - d);
			
			ans = min(ans, extra*5);
			if(sufx[xa] < xb)
				ans = min(ans, extra);
		}
		else{
			int extra = (xb-xa) - (yb-ya);
			if(extra & 1)
				extra ^= 1;
			
			int d = ya-prey[ya];
			if(d+d <= extra)
				ans = min(ans, (d+d)*5 + extra - d - d);
			
			d = sufy[yb]-yb;
			if(d+d <= extra)
				ans = min(ans, (d+d)*5 + extra - d - d);
			
			ans = min(ans, extra*5);
			if(sufy[ya] < yb)
				ans = min(ans, extra);
		}
		ans += v1;
		printf("%d\n", ans);
	}
}


