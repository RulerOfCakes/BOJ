#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll LNF = 1e18;
const int INF = 1e9;
int N, M, K;

class segtree {
public:
	vector<long long> tree;
	vector<long long> lazy; // lazy propagataion
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
		lazy.resize(size * 2);
	}
	void update(int node, long long x) {
		int idx = size + node - 1;
		long long diff = x - tree[idx];
		while (idx) {
			tree[idx] += diff;
			idx /= 2;
		}
	}
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
segtree coeff(100005), cons(100005);

//finding minimum value using given coefficients/constants
ll ternary_search(int l, int r){
    while(l+3<=r){
        int p = (l*2+r)/3;
        int q = (l + r*2)/3;
        ll a1 = coeff.getsum(1,1,coeff.size,p,p),
            a2 = coeff.getsum(1,1,coeff.size,q,q);
        ll b1 = cons.getsum(1,1,cons.size,p,p),
            b2 = cons.getsum(1,1,cons.size,q,q);
        if(a1*p + b1 > a2*q + b2){
            l=p;
        }
        else{
            r=q;
        }
    }
    ll ret = LNF;
    for(int i = l; i <= r; i++){
        ll a = coeff.getsum(1,1,coeff.size,i,i),
            b = cons.getsum(1,1,cons.size,i,i);
        ret=min(ret,a*i+b);
    }
    return ret;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c, d;
	cin >> N >> K;
    
    vector<int> heights(N+1), up(N+1), down(N+1);
    for(int i = 0; i < N; i++){
        cin >> heights[i];
    }
    for(int i = 0; i < N; i++){
        cin >> up[i];
    }
    for(int i = 0; i < N; i++){
        cin >> down[i];
    }
    ll ans = LNF;
    for(int i = 0; i < N; i++){
        //storing linear equation coefficients/constants in two segtrees
        coeff.update_range(1,1,coeff.size,1,heights[i]-1,-down[i]);
        coeff.update_range(1,1,coeff.size,heights[i],coeff.size,up[i]);

        cons.update_range(1,1,cons.size,1,heights[i]-1,down[i]*heights[i]);
        cons.update_range(1,1,cons.size,heights[i],cons.size,-up[i]*heights[i]);
        if(i>=K-1){
            //start calculating answers

            //minimum answer available from current updated array
            ans=min(ans,ternary_search(1,100000));

            //sliding window, remove the previous entries that are going to be
            //unused now
            int j = i - K + 1;
            coeff.update_range(1,1,coeff.size,1,heights[j]-1,down[j]);
            coeff.update_range(1,1,coeff.size,heights[j],coeff.size,-up[j]);
            cons.update_range(1,1,cons.size,1,heights[j]-1,-down[j]*heights[j]);
            cons.update_range(1,1,cons.size,heights[j],cons.size,up[j]*heights[j]);
        }
    }
    cout << ans;
}