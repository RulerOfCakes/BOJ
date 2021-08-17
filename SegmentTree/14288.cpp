#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;
vector<ll> money;
vector<vector<int>> v;
int l[100002],r[100002],order[100002];
void dfs(int cx, int &num){
    l[cx]=++num;
    for(int nx:v[cx]){
        dfs(nx,num);
    }
    r[cx]=num;
}
class segtree {
public:
	vector<long long> tree;
	//vector<long long> cnt; // count of lines
	//vector<long long> sum; // sum of squares
	vector<long long> lazy; // lazy propagataion
	int size;
    

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
		lazy.resize(size * 2);
		//cnt.resize(size * 2);
		//sum.resize(size * 2);
	}
    void init(int node, int nStart, int nEnd){
        if(nStart==nEnd){
            tree[node]=order[nStart];
            return;
        }
        int mid=(nStart+nEnd)/2;
        init(node*2,nStart,mid);
        init(node*2+1,mid+1,nEnd);
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


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c;
	cin >> N >> M;
	segtree seg(N);
    segtree nseg(N);
    money=vector<ll>(N+1,0);
    v=vector<vector<int>>(N+1,vector<int>());
    for(int i = 1; i <= N; i++){
        cin >> a;
        if(a==-1)continue;
        v[a].push_back(i);
    }
    b=0;
    dfs(1,b);
    for(int i = 1; i <= N; i++){
        order[l[i]] = money[i];
    }
    // seg.init(1,1,N);
    // nseg.init(1,1,N);
    ll x;
    bool toggle=0;
    while(M--){
        cin >> c;
        if(c==1){
            cin >> a >> x;
            if(!toggle)
            seg.update_range(1,1,N,l[a],r[a],x);
            else{
                nseg.update_range(1,1,N,l[a],l[a],x);
            }
        } else if(c==2){
            cin >> a;
            cout << seg.getsum(1,1,N,l[a],l[a])+nseg.getsum(1,1,N,l[a],r[a]) << '\n';
        }
        else{
            toggle=!toggle;
        }
    }
}