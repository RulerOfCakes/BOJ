#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;
vector<int> v;
//tree contains index of smallest element
class segtree {
public:
	vector<long long> tree;
	//vector<long long> cnt; // count of lines
	//vector<long long> sum; // sum of squares
	//vector<long long> lazy; // lazy propagataion
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
		//lazy.resize(size * 2);
		//cnt.resize(size * 2);
		//sum.resize(size * 2);
	}
    void init(int node, int nStart, int nEnd){
        if(nStart==nEnd)tree[node]=nStart;
        else{
            int mid = (nStart+nEnd)/2;
            init(node*2,nStart,mid);
            init(node*2+1,mid+1,nEnd);
            if(v[tree[node*2]]<=v[tree[node*2+1]]){
                tree[node]=tree[node*2];
            } else {
                tree[node]=tree[node*2+1];
            }
        }
    }
    //return smol index
	int query(int node, int nStart, int nEnd, int rStart, int rEnd){
		if(rStart>nEnd || nStart > rEnd){
            return -1;
        }
		if(rStart<=nStart&&nEnd<=rEnd){
            return tree[node];
        }
        int mid=(nStart+nEnd)/2;
        int m1 = query(node*2, nStart, mid, rStart, rEnd),
            m2 = query(node*2+1, mid+1, nEnd, rStart, rEnd);
		if(m1==-1){
            return m2;
        }else if(m2==-1){
            return m1;
        } else{
            if(v[m1]<=v[m2]){
                return m1;
            } else return m2;
        }
	}

    ll sol(int start, int end){
        int idx = query(1,0,N-1,start,end);
        
        if(idx==-1)return -1;
        ll ret = (ll)(end-start+1)*(ll)v[idx];
        if(start<=idx-1){
            ll tmp = sol(start, idx-1);
            if(ret<tmp){
                ret=tmp;
            }
        }
        if(idx+1<=end){
            ll tmp = sol(idx+1, end);
            if(ret<tmp){
                ret=tmp;
            }
        }
        return ret;
    }
	
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c;
	cin >> N;
	segtree seg(N);
    v = vector<int>(N);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    seg.init(1,0,N-1);
	cout << seg.sol(0,N-1);

	
	
}