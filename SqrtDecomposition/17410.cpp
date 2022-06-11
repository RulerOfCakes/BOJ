#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimization("unroll-loops")

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
int T, K, N, M;
int sz;
int arr[101010];
vector<int> buckets[400];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    sz = (int)sqrt(N);

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
        buckets[i / sz].push_back(arr[i]);
    }
    for (int i = 0; i < N / sz + 2; i++)
    {
        if (!buckets[i].empty())
            sort(buckets[i].begin(), buckets[i].end());
    }
    cin >> M;
    for (;M--;)
    {
        int a, b, c, d;
        cin >> a >> b >> c;
        if (a == 2)
        {
            int ans = 0;
            cin >> d;
            b--;
            c--;
            int lb = b / sz + 1 - (b % sz == 0);
            lb *= sz;
            int rb = (c/sz)*sz;
            if(lb<rb){
                for(int i = b; i < lb; i++){
                    ans+=(int)(arr[i]>d);
                }
                for(int i = rb; i <= c; i++){
                    ans+=(int)(arr[i]>d);
                }
                for(int i = lb/sz; i < rb/sz; i++){
                    ans+=buckets[i].end()-upper_bound(buckets[i].begin(),buckets[i].end(),d);
                }
            }
            else{
                for(int i = b; i <= c; i++){
                    ans+=(int)(arr[i]>d);
                }
            }
            cout << ans << '\n';
        }
        else
        {
            b--;
            buckets[b / sz].erase(lower_bound(buckets[b / sz].begin(), buckets[b / sz].end(), arr[b]));
            buckets[b / sz].insert(lower_bound(buckets[b / sz].begin(), buckets[b / sz].end(), c), c);
            arr[b] = c;
        }
    }
}