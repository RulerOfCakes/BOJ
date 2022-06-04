#include <bits/stdc++.h>

using namespace std;
using ll = int;
using base = complex<double>;

int N, K;

void fft(vector<base> &a, bool inv) {
    int n = (int) a.size();
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
        if(ret[i])ret[i]=1; // if you use int you need this
    }
    return ret;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> N >> K;

    vector<ll> ret(1002),bv(1002);
	for(int i = 0; i < N; i++){
        int a;cin>>a;
        bv[a]=1;
    }
    ret[0]=1;
    while(K){
        if(K&1)ret=multiply(ret,bv);
        K>>=1;
        bv=multiply(bv,bv);
    }
    for(int i = 1; i < ret.size(); i++){
        if(ret[i])cout << i << ' ';
    }
}