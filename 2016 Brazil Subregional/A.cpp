#include<bits/stdc++.h>
using namespace std;

int main(){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if(a == b || a == c || b == c || a == b + c || b == a + c || c == a + b)
        puts("S");
    else
        puts("N");
}
