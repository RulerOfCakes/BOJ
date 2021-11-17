#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, int>;
int N;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    int lnum = N - 2;
    ll ans = 0;
    vector<int> v(N);
    vector<int> count(N);
    // next increased cost, index
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
        count[i] = 1;
        pq.push({v[i] * 3, i});
        ans += v[i];
    }
    if(N==1){
        cout << 0;
        return 0;
    }
    for (int i = 0; i < lnum; i++)
    {
        auto cur = pq.top();
        pq.pop();
        ll nexc = cur.first;
        int idx = cur.second;
        int cnt = ++count[idx];
        ll nnexc = (((ll)(cnt + 1) * (cnt + 1)) - ((ll)cnt * cnt)) * v[idx];
        ans += nexc;
        pq.push({nnexc, idx});
    }
    cout << ans;
}
// 9 16
// 9 4
// 16 3