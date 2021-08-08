#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using ppi = pair<pi, pi>;

int T, N, M;
const int INF = 1e5 + 1;

vector<int> ylist;

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

	void update_lazy(int node, int start, int end) {
		if (!lazy[node])return;
		tree[node] += lazy[node] * (end - start + 1);
		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
	void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, int diff) {
		update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd)return;
		if (nStart >= rStart && nEnd <= rEnd) {
			lazy[node] = diff;
			update_lazy(node, nStart, nEnd);
			return;
		}
		
		int mid = (nStart + nEnd) / 2;
		update_range(node*2, nStart, mid, rStart, rEnd, diff);
		update_range(node*2+1, mid + 1, nEnd, rStart, rEnd, diff);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
	long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
		update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd) return 0;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c, d;
    cin >> T;
    while (T--)
    {
        ylist = vector<int>();
        map<int,int> ycds;
        cin >> N >> M;
        
        vector<pi> folks;
        vector<ppi> v;
        //v layout
        //{{starting point, start/finish}, {ybottom, ytop}}
        for (int i = 0; i < N; i++)
        {
            cin >> a >> b;
            a+=2;
            b+=2;
            folks.push_back({a, b});
            ylist.push_back(b);
        }
        for (int i = 0; i < M; i++)
        {
            cin >> a >> b >> c >> d;
            a+=2;
            b+=2;
            c+=2;
            d+=2;
            
            v.push_back({{a-1, 0}, {c, d}});
            v.push_back({{b, 1}, {c, d}});
            ylist.push_back(b);
            ylist.push_back(d);
        }
        sort(folks.begin(), folks.end());
        sort(v.begin(), v.end());
        sort(ylist.begin(), ylist.end());
        ylist.erase(unique(ylist.begin(), ylist.end()), ylist.end());
        for(int i = 0; i < ylist.size(); i++){
            ycds[ylist[i]]=i+1;
        }
        ll ans = 0;ll mns=0;
        segtree seg(ylist.size());
        int idx = 0;
        for (int i = 0; i < v.size(); i++)
        {

            int cx = v[i].first.first, param = v[i].first.second,
                tsy = v[i].second.first, tey = v[i].second.second;
            int sy = lower_bound(ylist.begin(), ylist.end(), tsy) - ylist.begin() + 1;
            int ey = lower_bound(ylist.begin(), ylist.end(), tey) - ylist.begin() + 1;
            while(idx<folks.size() && cx>=folks[idx].first){
                //cout << "hoho\n";
                seg.update_range(1,1,seg.size,ycds[folks[idx].second],ycds[folks[idx].second],1);
                idx++;
            }
            if (param == 0)
            {
                mns+=seg.getsum(1,1,seg.size, sy, ey);
                //seg.update_range(1, 1, ylist.size() - 1, sy, ey - 1, 1);
            }
            else
            {
                ans+=seg.getsum(1,1,seg.size, sy, ey);
                
                //seg.update_range(1, 1, ylist.size() - 1, sy, ey - 1, -1);
            }
           
        }
        cout << ans-mns << '\n';
    }
}