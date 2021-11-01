#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    vector<int> v(N);

    ll cnt = 0;
    ll tsum = 0;

    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
        tsum += v[i];
    }
    for (int i = 0; i < N; i++)
    {
        ll cx = v[i];
        if(cx<0){
            ll tcx=-cx;
            cnt+=(tcx-1)/tsum+1;
        }
        for (int j = (i + 1) % N; j != i; j = (j + 1) % N)
        {
            cx += v[j];
            if (cx < 0)
            {
                ll tcx=-cx;
                cnt += (tcx - 1) / tsum + 1;
            }
        }
    }

    cout << cnt;
}