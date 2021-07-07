#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using ppi = pair<pi, pi>;

int T, N;
// const int INF = 2e5 + 1;
const int MOD = 1e9 + 7;

class segtree
{
public:
   // vector<long long> tree;
    vector<long long> cnt; // count of lines
    vector<long long> sum; // sum of squares
    //vector<long long> lazy; // lazy propagataion
    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        //tree.resize(size * 2, 0);
        //lazy.resize(size * 2);
        cnt.resize(size * 2);
        sum.resize(size * 2);
    }
    // void update(int node, long long x)
    // {
    //     int idx = size + node - 1;
    //     long long diff = x - tree[idx];
    //     while (idx)
    //     {
    //         tree[idx] += diff;
    //         idx /= 2;
    //     }
    // }
    
    void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, int diff)
    {
        
        if (nEnd < rStart || nStart > rEnd)
            return;
        if (nStart >= rStart && nEnd <= rEnd)
        {
            cnt[node]+=diff;
            
        }
        else{
            int mid = (nStart + nEnd) / 2;
            update_range(node * 2, nStart, mid, rStart, rEnd, diff);
            update_range(node * 2 + 1, mid + 1, nEnd, rStart, rEnd, diff);
            
        }

        if(cnt[node]>0){
            sum[node]=nEnd-nStart+1;
        }
        else if(nStart!=nEnd){
            sum[node]=sum[node*2]+sum[node*2+1];
        }
        else{
            sum[node]=0;
        }

        
    }
    long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd)
    {
        
        if (nEnd < rStart || nStart > rEnd)
            return 0;
        if (rStart <= nStart && rEnd >= nEnd)
            return sum[node];
        int mid = (nStart + nEnd) / 2;
        return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    }
    
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c, d;

    cin >> N;
    segtree seg(30002);
    vector<ppi> v;
    //v layout
    //{{starting point, start/finish}, {ybottom, ytop}}
    for (int i = 0; i < N; i++)
    {
        cin >> a >> b >> c >> d;
        a++;b++;c++;d++;
        v.push_back({{a,0},{b,d}});
        v.push_back({{c,1},{b,d}});
    }
    sort(v.begin(), v.end());
    
    ll ans = 0;
    
    int prev = 0;
    for (int i = 0; i < v.size(); i++)
    {
        
        int cx = v[i].first.first, param = v[i].first.second,
            sy = v[i].second.first, ey = v[i].second.second;
        int dx = cx-prev;
        if(i!=0)
        ans += dx*seg.getsum(1,1,seg.size,1,30002);
        prev=cx;
        if(param==0){
            seg.update_range(1,1,seg.size,sy,ey-1,1);
        }
        else{
            seg.update_range(1,1,seg.size,sy,ey-1,-1);
        }
    }
    cout << ans << '\n';
}