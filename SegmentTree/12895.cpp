#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N,T,Q;

class segtree {
public:
	vector<long long> tree;
	vector<long long> lazy; // lazy propagataion
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 1);
		lazy.resize(size * 2);
	}
	void update_lazy(int node, int start, int end) {
		if (!lazy[node])return;
		tree[node] = lazy[node];
		if (start != end) {
			lazy[node * 2] = lazy[node];
			lazy[node * 2 + 1] = lazy[node];
		}
		lazy[node] = 0;
	}
	void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, ll diff) {
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
		tree[node] = tree[node * 2] | tree[node * 2 + 1];
	}
	long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
		update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd) return 0;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return getsum(node * 2, nStart, mid, rStart, rEnd) | getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	}
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>T>>Q;
    segtree seg(N+2);
    
    for(int i = 0; i < Q; i++){
        char cmd;ll a,b,c;
        cin>>cmd>>a>>b;
        if(a>b)swap(a,b);
        if(cmd=='C'){
            cin>>c;
            seg.update_range(1,1,seg.size,a,b,(1<<(c-1)));
        }
        else{
            ll res = seg.getsum(1,1,seg.size,a,b);
            ll out = 0;
            while(res){
                if(res&1)out++;
                res>>=1;
            }
            cout << out << '\n';
        }
    }
}