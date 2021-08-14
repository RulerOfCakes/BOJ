#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;
bool primes[4000004];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K >> M;
    for (int i = 2; i * i <= N; i++)
    {
        if (primes[i])
            continue;
        for (int j = i * i; j <= N; j += i)
        {
            primes[j] = true;
        }
    }
    vector<ll> pv;
    for (int i = 2; i <= N; i++)
    {
        if (!primes[i])
            pv.push_back(i);
    }

    vector<ll> cnt(pv.size());
    for (int i = 0; i < pv.size(); i++)
    {
        for (ll j = pv[i]; j <= N; j *= pv[i])
        {
            cnt[i]+=((N/j)-(K/j)-((N-K)/j));
        }
    }
    ll ans = 1;
    for(int i = 0; i < cnt.size(); i++){
        for(int j = 0; j < cnt[i]; j++){
            ans*=pv[i];ans%=M;
            
        }
    }
    cout << ans;
}