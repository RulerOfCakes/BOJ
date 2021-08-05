#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M;

class segtree2d {
public:
	vector<vector<ll>> tree;
	
	int size;

	segtree2d (int n) {
		size=n;
        tree=vector<vector<ll>>(2*n+2, vector<ll>(2*n+2));
		//cnt.resize(size * 2);
		//sum.resize(size * 2);
	}
    void init(vector<vector<ll>>& v){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                tree[i+size][j+size]=v[i][j];
            }
        }
        for(int i = size; i < 2*size; i++){
            for(int j = size-1; j > 0; j--){
                tree[i][j]=tree[i][j<<1]+tree[i][j<<1|1];
            }
        }

        for(int i = size-1; i > 0; i--){
            for(int j = 1; j < 2*size; j++){
                tree[i][j]=tree[i<<1][j]+tree[i<<1|1][j];
            }
        }
    }
	void update(int x, int y, long long val) {
		tree[x+size][y+size]=val;

        for(int i = y+size; i > 1; i>>=1){
            tree[x+size][i>>1]=tree[x+size][i]+tree[x+size][i^1];
        }

        for(x = x+size; x > 1; x >>= 1){
            for(int i  = y+size; i >= 1; i>>=1){
                tree[x>>1][i]=tree[x][i]+tree[x^1][i];
            }
        }
	}
    ll get1dsum(int x, int y1, int y2){
        ll ret = 0;
        for(y1+=size, y2+=size+1; y1<y2; y1>>=1,y2>>=1){
            if(y1&1)ret+=tree[x][y1++];
            if(y2&1)ret+=tree[x][--y2];
        }
        return ret;
    }
	long long getsum(int x1, int y1, int x2, int y2) {
		ll ret = 0;
        for(x1 += size, x2 += size+1; x1 < x2; x1>>=1,x2>>=1){
            if(x1&1)ret+=get1dsum(x1++,y1,y2);
            if(x2&1)ret+=get1dsum(--x2,y1,y2);
        }
        return ret;
		
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c;
	cin >> N >> M;
	segtree2d seg(N);
	ll ans = 0;
	vector<vector<ll>> inputs;
	for (int i = 0; i < N; i++) {
        vector<ll> tmpv;
		for(int j = 0; j < N; j++){
            
            cin >> a;
            tmpv.push_back(a);
        }
        inputs.push_back(tmpv);
	}
    seg.init(inputs);
    for(int i = 0; i < M; i++){
        int d;
        cin >> a >> b >> c >> d;
        if(a==0){
            seg.update(b-1,c-1,d);
        }
        else if(a==1){
            int e;
            cin >> e;
            cout << seg.getsum(b-1,c-1,d-1,e-1) << '\n';
        }
    }
}