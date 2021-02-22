#include <bits/stdc++.h>

using namespace std;

long long N, M;
//NOTE: refrain from using assignment operators when nearing arithmetic overflows
//shortened phi with naive factorization
long long phi(long long n){
    long long ret = n;
    long long f = 2;
    while(f*f <= n){
        if(n%f==0) ret = ret / f * (f-1);
        while(n%f == 0) n /= f;
        f++;
    }
    if(n!=1)ret = ret / n*(n-1);
    return ret;
}
//modular exponentiation with binary bitwise operators
long long z(long long n, long long m, long long o){
    long long ret  = 1;
    while(m){
        if(m & 1) ret = ret * n % o;
        m >>= 1;
        n = n * n % o;
    }
    return ret;
}

//naive factorization
long long naive(long long n, long long m){
    if(n==1)return 1;
    return z(n, naive(n-1, m), m);
}

long long sol(long long n, long long m){
    if(m == 1)return 1;
    else if(n <= 5){
        return naive(n, m);
    }
    else{
        return z(n, sol(n-1, phi(m)) + phi(m), m);
    }
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    cout << sol(N, M) % M;
}