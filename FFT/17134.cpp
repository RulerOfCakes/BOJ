#include <bits/stdc++.h>

using namespace std;
using ll = int;
using base = complex<double>;

int N, T;
const int SIZE = 1<<20;
void fft(vector<base> &a, bool inv) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        double x = inv ? M_PI / i : -M_PI / i;
        base w = {cos(x), sin(x)};
        for (int j = 0; j < n; j += i << 1) {
            base th = {1, 0};
            for (int k = 0; k < i; k++) {
                base tmp = a[i + j + k] * th;
                a[i + j + k] = a[j + k] - tmp;
                a[j + k] += tmp;
                th *= w;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}

vector<ll> multiply(const vector<ll> &y, const vector<ll> &z) {
    vector<base> a(y.begin(), y.end()), b(z.begin(), z.end());
    int n = 2;
    while(n<y.size()+z.size())n<<=1;
    a.resize(n); b.resize(n);
    fft(a, false);
    fft(b, false);
    for(int i = 0; i < n; i++){
        a[i] *= b[i];
    }
    fft(a, true);
    vector<ll> ret(n);
    for (int i = 0; i < n; i++) {
        ret[i] = (ll)round(a[i].real());
    }
    return ret;
}

bool prime[SIZE];
bool semiprime[SIZE];
vector<ll> pv(SIZE),sv(SIZE);
vector<int> primev;
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> T;
    for(register long long i = 2; i <= 1'000'000; i++){
        if(!prime[i]){
            primev.push_back(i);
            for(long long j = i*i; j <= 1'000'000; j+=i){
                prime[j]=1;
            }
        }
    }
    for(int i = 0; i < primev.size(); i++){
        if(primev[i]%2)pv[primev[i]]=1;
        sv[primev[i]*2]=1;
    }
    
    auto ret = multiply(pv, sv);
    while(T--){
        cin>>N;
        cout << ret[N] << '\n';
    }
}