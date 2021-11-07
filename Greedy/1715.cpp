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
    priority_queue<int, vector<int>, greater<int>> pq;
    while (N--)
    {
        int a;
        cin >> a;
        pq.push(a);
    }
    ll ans = 0;
    while (pq.size() > 1)
    {
        int c1 = pq.top();
        pq.pop();
        if (pq.empty())
        {
            pq.push(c1);
            break;
        }
        int c2 = pq.top();
        pq.pop();
        ans += c1 + c2;
        pq.push(c1 + c2);
    }
    cout << ans;
}