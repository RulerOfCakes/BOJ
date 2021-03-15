#include <bits/stdc++.h>
//pollard's rho algorithm
using namespace std;
using ll = long long;
ll N;
vector<ll> alist = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
//x*y % m, overflow safe calculation
ll mulmod(ll p, ll q, ll m){
    p %= m;
    q %= m;
    ll r = 0;
    ll w = p;
    while(q){
        if(q%2){
            r = (r+w)%m;
        }
        w = (w+w)%m;
        q >>= 1;
    }
    return r;
}

//x^y % m, overflow safe calculation
ll powmod(ll x, ll y, ll m){
    x %= m;
    ll r = 1ll;
    while(y>0){
        if(y&1)r = mulmod(r, x, m);
        x = mulmod(x, x, m);
        y /= 2;
    }
    return r;
}

bool miller_rabin(ll n, ll a) {
    if(!n%a)return false;
    ll d = n-1;
    while(true){
        ll tmp = powmod(a, d, n);
        if(d&1)return (tmp != 1 && tmp != n-1);
        else if (tmp == n-1)return false;
        d >>= 1;
    }
}

bool prime_test(ll n){
    if(n <= 1)return false;
    for(ll a : alist){
        if(n == a)return true;
        if(n > 40 && miller_rabin(n, a))return false;
    }
    if(n <= 40)return false;
    return true;
}

ll gcd(ll a, ll b){
    if(b==0)return a;
    else return gcd(b, a%b);
}

vector<ll> factors;
void factorize(ll n){
    if(n==1)return;
    //VERY IMPORTANT IF STATEMENT, THIS ONE COST ME 2 HOURS WORTH OF SANITY
    if(n%2==0){
        factors.push_back(2);
        factorize(n/2);
        return;
    }
    if(prime_test(n)){
        factors.push_back(n);
        return;
    }
    ll x, y, c, g = n;
    //f(x) = (x^2 + c) mod n
    auto f = [&](ll x){
        return (mulmod(x, x, n)+c)%n;
    };
    do{
        if(g==n){
            x = y = rand() % (n-2) + 2;
            c = rand() % 20 + 1;
            g = 1;
        }
        x = f(x);
        y = f(f(y));
        g = gcd(abs(x-y), n);
    } while (g == 1);
    factorize(g);
    factorize(n/g);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    if(N == 1){
        cout << 1;
        return 0;
    }
    factorize(N);
    sort(factors.begin(), factors.end());
    ll ans = 1, temp = 1, prev = factors[0];
    for(ll i = 1; i < factors.size(); i++){
        if(factors[i] != prev){
            ans *= (ll)pow(prev, temp-1)*(prev-1);
            prev = factors[i];
            temp = 1;
        } else {
            temp++;
        }
    }
    cout << (ll)(ans*(prev-1)*(ll)pow(prev, temp-1));
}
