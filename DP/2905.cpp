#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N, M;
int arr[1000002]; //input heights

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    deque<pi> dq;
    ll res = 0, cnt = 0;
    ll prev = -1;
    int lastidx = 0;
    for (int i = 0; i <= N; i++)
    {
        if(i!=N)
        cin >> arr[i];
        res += arr[i];

        while (!dq.empty() && dq.back().second > arr[i])
            dq.pop_back();
        dq.push_back({i, arr[i]});
        if (i==M){
            prev=dq.front().second;
        }
        if (i >= M)
        {
            if (prev != dq.front().second)
            {
                cnt += ((i - lastidx) - 1) / M + 1;
                res -= (ll)(i - lastidx) * prev;
                lastidx = i;
                prev = dq.front().second;
            }
            if (dq.front().first <= i - M)
            {
                int cidx = dq.front().first;
                dq.pop_front();
                if (prev != dq.front().second)
                {
                    cnt += (cidx - lastidx) / M + 1;
                    res -= (ll)(cidx - lastidx+1) * prev;
                    lastidx = cidx+1;
                    prev = dq.front().second;
                }
            }
        }
    }
    cout << res << '\n'
         << cnt;
}