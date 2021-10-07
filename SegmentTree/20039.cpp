#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll LNF = 1e18;
const int INF = 1e9;
int N, M, K;

class segtree {
public:
	vector<int> tree;
	//vector<long long> lazy; // lazy propagataion
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
		//lazy.resize(size * 2);
	}
    segtree(int n, int x){
        for(size = 1; size < n; size*=2);
        tree.resize(size*2,x);
    }
	void update(int node, int x) {
		int idx = size + node - 1;
		tree[idx]=max(tree[idx],x);
        idx/=2;
		while (idx) {
			tree[idx] =max(tree[idx*2],tree[idx*2+1]);
			idx /= 2;
		}
	}
	// void update_lazy(int node, int start, int end) {
	// 	if (!lazy[node])return;
	// 	tree[node] += lazy[node] * (end - start + 1);
	// 	if (start != end) {
	// 		lazy[node * 2] += lazy[node];
	// 		lazy[node * 2 + 1] += lazy[node];
	// 	}
	// 	lazy[node] = 0;
	// }
	// void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, int diff) {
	// 	update_lazy(node, nStart, nEnd);
	// 	if (nEnd < rStart || nStart > rEnd)return;
	// 	if (nStart >= rStart && nEnd <= rEnd) {
	// 		lazy[node] = diff;
	// 		update_lazy(node, nStart, nEnd);
	// 		return;
	// 	}
		
	// 	int mid = (nStart + nEnd) / 2;
	// 	update_range(node*2, nStart, mid, rStart, rEnd, diff);
	// 	update_range(node*2+1, mid + 1, nEnd, rStart, rEnd, diff);
	// 	tree[node] = tree[node * 2] + tree[node * 2 + 1];
	// }
	// long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
	// 	update_lazy(node, nStart, nEnd);
	// 	if (nEnd < rStart || nStart > rEnd) return 0;
	// 	if (rStart <= nStart && rEnd >= nEnd) return tree[node];
	// 	int mid = (nStart + nEnd) / 2;
	// 	return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	// }
    int getmax(int node, int nStart, int nEnd, int rStart, int rEnd) {
		if (nEnd < rStart || nStart > rEnd) return -1e9;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return max(getmax(node * 2, nStart, mid, rStart, rEnd), getmax(node * 2 + 1, mid+1, nEnd, rStart, rEnd));
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c, d;
	cin >> N;
    vector<segtree> seg(4,segtree(N+2,-1e9));
    vector<int> v, xlist;
    v.push_back(0);
    for(int i = 0; i < N; i++){
        cin >> a;
        xlist.push_back(a);
        v.push_back(a);
    }
    //value compression
    sort(xlist.begin(),xlist.end());
    xlist.erase(unique(xlist.begin(),xlist.end()),xlist.end());
    //revaluing v
    for(int i = 1; i <= N; i++){
        v[i]=(lower_bound(xlist.begin(),xlist.end(),v[i])-xlist.begin()) + 1;
    }
    int cN = seg[0].size;
    seg[0].update(v[1],0);seg[2].update(v[1],0);
    for(int i = 2; i <= N; i++){
        a=max({seg[0].getmax(1,1,cN,v[i]+1,N),seg[1].getmax(1,1,cN,v[i]+1,N),seg[3].getmax(1,1,cN,v[i]+1,N)})+1;
        b=max({seg[0].getmax(1,1,cN,v[i]+1,N),seg[1].getmax(1,1,cN,v[i]+1,N)})+1;
        c=max({seg[1].getmax(1,1,cN,1,v[i]-1),seg[2].getmax(1,1,cN,1,v[i]-1),seg[3].getmax(1,1,cN,1,v[i]-1)})+1;
        d=max({seg[2].getmax(1,1,cN,1,v[i]-1),seg[3].getmax(1,1,cN,1,v[i]-1)})+1;

        if(a==1)a=2;
        if(b==1)b=0;
        if(c==1)c=2;
        if(d==1)d=0;
        seg[0].update(v[i],0);seg[2].update(v[i],0);
        seg[0].update(v[i],max(a,b));seg[1].update(v[i],b);
        seg[2].update(v[i],max(c,d));seg[3].update(v[i],d);
    }

    cout << max({0,seg[1].getmax(1,1,cN,1,N),seg[3].getmax(1,1,cN,1,N)});
}