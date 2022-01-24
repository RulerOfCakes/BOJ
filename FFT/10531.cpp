#include <bits/stdc++.h>

using namespace std;
using base = complex<double>;
using ll = long long;
int N;

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
    }
    return ret;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<ll> a(200002), b(200002);
    for(int i = 0; i < N; i++){
        int t;
        cin >> t;
        a[t]=b[t]=1;
    }
    a[0]=b[0]=1;//1 stroke
    auto ret = multiply(a,b);
    int cnt=0,M;

    cin>>M;
    for(int i = 0; i < M; i++){
        int t;cin>>t;
        if(ret[t])cnt++;
    }
    cout << cnt;
}