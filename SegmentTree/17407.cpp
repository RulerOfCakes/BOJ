#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, Q;
vector<ll> psum;
class segtree {
public:
	vector<long long> tree;
	//vector<long long> cnt; // count of lines
	//vector<long long> sum; // sum of squares
	vector<long long> lazy; // lazy propagataion

	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2);
		lazy.resize(size * 2);
		//cnt.resize(size * 2);
		//sum.resize(size * 2);
	}
	// void update(int node, long long x) {
	// 	int idx = size + node - 1;
	// 	tree[idx]=x;
    //     idx/=2;
	// 	while (idx) {
	// 		tree[idx] =min(tree[idx*2],tree[idx*2+1]);
	// 		idx /= 2;
	// 	}
	// }
    void init(int node, int start, int end){
        if(start==end){
            tree[node]=psum[start];
            return;
        }
        int mid = (start+end)/2;
        init(node*2,start,mid);init(node*2+1,mid+1,end);
        tree[node]=min(tree[node*2],tree[node*2+1]);
    }
	void update_lazy(int node, int start, int end) {
		if (!lazy[node])return;
		tree[node] += lazy[node];// * (end - start + 1);
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
		tree[node] = min(tree[node * 2],  tree[node * 2 + 1]);
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
    string s;
	cin >> s;
    int L = s.length();
	segtree seg(L+1);
    psum=vector<ll>(L+1);
    
    int sum=0;
    for(int i = 0; i < L; i++){
        if(s[i]=='('){
            sum++;
            psum[i+1]=psum[i]+1;
        }
        else{
            sum--;
            psum[i+1]=psum[i]-1;
        }
    }
    seg.init(1,1,L);
    cin >> Q;	
    
    int ans=0;
	for (int n = 0; n < Q; n++) {
		cin >> a;
        int k = (s[a-1]=='('?-2:2);
        seg.update_range(1,1,L,a,L,k);
        s[a-1]=(s[a-1]=='('?')':'(');
        
        sum+=k;
        
        
        //cout << seg.tree[1] << ' ' << sum << "\n\n";
        if(seg.tree[1]>=0&&sum==0)ans++;
	}

	cout << ans;
	
}