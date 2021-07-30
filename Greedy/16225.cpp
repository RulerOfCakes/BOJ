#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N;
vector<pi> arr;
int A[200002];
int B[200002];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
    }
    for (int i = 0; i < N; i++)
    {
        arr.push_back({A[i], B[i]});
    }
    sort(arr.begin(), arr.end(), [&](pi &a, pi &b)
         {
             if (a.second == b.second)
                 return a.first < b.first;
             else
                 return a.second < b.second;
         });
    ll ans = arr[0].first;
    priority_queue<int> pq;
    for (int i = 1; i < N / 2; i++)
    {
        pq.push(arr[2 * i].first);
        pq.push(arr[2 * i - 1].first);
        //since the array is sorted, we can always take one from these two
        //if we make the optimal choices each turn
        ans+=pq.top();
        pq.pop();
    }
    cout << ans;
}