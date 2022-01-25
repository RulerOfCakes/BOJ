#include <bits/stdc++.h>
using namespace std;
int N,M;

int gcd(int a, int b){
    if(b==0)return a;
    return gcd(b,a%b);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    int a=0,b=INT_MAX/N;
    int mult = M/N;
    for(int i = 1; i <= sqrt(mult); i++){
        if(mult%i)continue;
        int tmp=mult/i;
        if(gcd(tmp,i)!=1)continue;
        if(abs(i-tmp)<abs(a-b))a=i,b=tmp;
    }

    cout << a*N << ' ' << b*N;
}