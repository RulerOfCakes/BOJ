#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
int N;
vector<ull> alist = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
// //x*y % m, overflow safe calculation
// ll mulmod(ll p, ll q, ll m){
//     p %= m;
//     q %= m;
//     ll r = 0;
//     ll w = p;
//     while(q){
//         if(q%2){
//             r = (r+w)%m;
//         }
//         w = (w+w)%m;
//         q >>= 1;
//     }
//     return r;
// }
inline ull mulmod(ull p, ull q, ull m){
    return (ull)((__int128_t)p * q % m);
}

//x^y % m, overflow safe calculation
ull powmod(ull x, ull y, ull m){
    x %= m;
    ull r = 1ULL;
    while(y){
        if(y&1)r = mulmod(r, x, m);
        x = mulmod(x, x, m);
        y >>= 1;
    }
    return r;
}

inline bool miller_rabin(ull n, ull a) {
    if(n%a==0)return 0;
    ull d = n-1;
    int cnt=-1;
    while(!(d&1)){
        cnt++;
        d>>=1;
    }
    ull tmp = powmod(a,d,n);
    if(tmp==1 or tmp==n-1) return 1;
    while(cnt--){
        tmp=mulmod(tmp,tmp,n);
        if(tmp==n-1)return true;
    }
    return false;
}

bool prime_test(ull n){
    if(n <= 1)return false;
    for(ull a : alist){
        if(n == a)return true;
        if(n > 40 && !miller_rabin(n, a))return false;
    }
    if(n <= 40)return false;
    return true;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    int cnt=0;
    for(int i = 0; i < N; i++){
        ull a;
        cin >> a;
        if(prime_test(2*a+1))cnt++;
    }
    
    cout << cnt << '\n';
    
}