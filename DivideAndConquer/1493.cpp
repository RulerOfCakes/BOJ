#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N, M, K;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c;
    int l, w, h;
    cin >> l >> w >> h;
    cin >> N;
    vector<pi> v;
    for (int i = 0; i < N; i++)
    {
        cin >> a >> b;
        v.push_back({a, b});
    }
    ll ans = 0, b4 = 0;
    for(int i = N-1; i >= 0; i--){
        b4 <<= 3; //since unit volume is going down by 2^3, we multiply
        //the previous number of cubes used by 2^3 to accurately count smaller cubes

        //dividing the boxes by 2^ix2^ix2^i, minus the volume of previously accounted cubes
        ll pc = (ll)(l>>i)*(w>>i)*(h>>i)-b4;
        ll nc = min((ll)v[i].second, pc);

        b4 += nc;
        ans += nc;
    }
    if(b4 == (ll)l*w*h)cout << ans;
    else cout << -1;
}