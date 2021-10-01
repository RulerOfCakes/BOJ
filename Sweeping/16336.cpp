#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using ppi = pair<pi, pi>;

int Q;

class segtree
{
public:
    vector<long long> tree;
    // vector<long long> cnt; // count of lines
    // vector<long long> sum; // sum of squares
    vector<long long> lazy; // lazy propagataion
    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2, 0);
        lazy.resize(size * 2);
        // cnt.resize(size * 2);
        // sum.resize(size * 2);
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

    void update_lazy(int node, int start, int end)
    {
        if (!lazy[node])
            return;
        tree[node] += lazy[node] * (end - start + 1);
        if (start != end)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, int diff)
    {
        update_lazy(node, nStart, nEnd);
        if (nEnd < rStart || nStart > rEnd)
            return;
        if (nStart >= rStart && nEnd <= rEnd)
        {
            lazy[node] = diff;
            update_lazy(node, nStart, nEnd);
            return;
        }

        int mid = (nStart + nEnd) / 2;
        update_range(node * 2, nStart, mid, rStart, rEnd, diff);
        update_range(node * 2 + 1, mid + 1, nEnd, rStart, rEnd, diff);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
    long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd)
    {
        update_lazy(node, nStart, nEnd);
        if (nEnd < rStart || nStart > rEnd)
            return 0;
        if (rStart <= nStart && rEnd >= nEnd)
            return tree[node];
        int mid = (nStart + nEnd) / 2;
        return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid + 1, nEnd, rStart, rEnd);
    }
};

vector<int> qtypes;
vector<pi> q1;
vector<int> q1idx;
vector<ppi> q2;
vector<int> q2idx;
map<int, int> ycds;
vector<int> ylist;
vector<ll> ANS;

void special(int l, int m, int r){
    auto iter1 = lower_bound(q1idx.begin(),q1idx.end(), l);
    vector<pi> tq1;
    vector<ppi> tq2;
    while(*iter1 <= m){
        int ridx=iter1-q1idx.begin();
        int a, b;
        tie(a,b) = q1[ridx];
        tq1.push_back({a,ycds[b]});
        iter1++;
    }
    sort(tq1.begin(),tq1.end());
    auto iter2 = lower_bound(q2idx.begin(),q2idx.end(),m+1);
    //auto iter2 = q2idx.begin();
    while(*iter2 <= r){
        int ridx=iter2-q2idx.begin();
        int a=q2[ridx].first.first,b=q2[ridx].first.second,c=q2[ridx].second.first,d=q2[ridx].second.second;
        ppi tppi = {{a,b},{ycds[c],ycds[d]}};
        tq2.push_back(tppi);
        iter2++;
    }
    sort(tq2.begin(),tq2.end());
    segtree seg(ylist.size()+1);
    ll ans = 0;
    ll mns = 0;
    
    int idx = 0;
    for (int i = 0; i < tq2.size(); i++)
    {

        int cx = tq2[i].first.first, param = tq2[i].first.second,
            sy = tq2[i].second.first, ey = tq2[i].second.second;
        
        while (idx < tq1.size() && cx >= tq1[idx].first)
        {
            //cout << "hoho\n";
            seg.update_range(1, 1, seg.size, tq1[idx].second, tq1[idx].second, 1);
            idx++;
        }
        if (param == 0)
        {
            mns += seg.getsum(1, 1, seg.size, sy, ey);
            //seg.update_range(1, 1, ylist.size() - 1, sy, ey - 1, 1);
        }
        else
        {
            ans += seg.getsum(1, 1, seg.size, sy, ey);

            //seg.update_range(1, 1, ylist.size() - 1, sy, ey - 1, -1);
        }
    }
    cout << l << ' ' << m << ' ' << r << '\n';
    cout << ans-mns << "!" << '\n';
    for(int i = m+1; i <= r; i++){
        ANS[i]+=ans-mns;
    }
}

void sol(int l, int r){
    if(l==r){
        // if(qtypes[l]==1){

        // }
        // else{

        // }
        return;
    }
    int m = (l+r)/2;
    sol(l,m);sol(m+1,r);
    special(l,m,r);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> Q;

    for(int i = 0; i < Q; i++){
        int a,b,c,d,e;
        cin >> a >> b >> c;
        b++;c++;qtypes.push_back(a);
        if(a==1){
            q1.push_back( {b,c});
            q1idx.push_back(i);
            ylist.push_back(c);
        }
        else if(a==2){
            cin >> d >> e;
            d++;e++;
            q2.push_back( {{b-1,0},{c,e}});
            q2.push_back( {{d,1},{c,e}});
            q2idx.push_back(i);
            q2idx.push_back(i);

            ylist.push_back(c);
            ylist.push_back(e);
        }
    }
    sort(ylist.begin(), ylist.end());
    ylist.erase(unique(ylist.begin(), ylist.end()), ylist.end());
    for (int i = 0; i < ylist.size(); i++)
    {
        ycds[ylist[i]] = i + 1;
    }
    ANS= vector<ll>(Q,0);
    sol(0,Q-1);
    
    for(int i = 0; i < Q; i++){
        cout << ANS[i] << '\n';
    }
    
}