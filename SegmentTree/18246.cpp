#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using ppi = pair<pi, pi>;

int T, N, M;
const int INF = 1e5 + 1;

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
                tree[i][j]=max(tree[i][j<<1],tree[i][j<<1|1]);
            }
        }

        for(int i = size-1; i > 0; i--){
            for(int j = 1; j < 2*size; j++){
                tree[i][j]=max(tree[i<<1][j],tree[i<<1|1][j]);
            }
        }
    }
	// void update(int x, int y, long long val) {
	// 	tree[x+size][y+size]=val;

    //     for(int i = y+size; i > 1; i>>=1){
    //         tree[x+size][i>>1]=tree[x+size][i]+tree[x+size][i^1];
    //     }

    //     for(x = x+size; x > 1; x >>= 1){
    //         for(int i  = y+size; i >= 1; i>>=1){
    //             tree[x>>1][i]=tree[x][i]+tree[x^1][i];
    //         }
    //     }
	// }
    // ll get1dsum(int x, int y1, int y2){
    //     ll ret = 0;
    //     for(y1+=size, y2+=size+1; y1<y2; y1>>=1,y2>>=1){
    //         if(y1&1)ret+=tree[x][y1++];
    //         if(y2&1)ret+=tree[x][--y2];
    //     }
    //     return ret;
    // }
	ll get1dquery(int x, int y1, int y2){
		ll ret = 0;
        for(y1+=size, y2+=size+1; y1<y2; y1>>=1,y2>>=1){
            if(y1&1)ret=max(ret,tree[x][y1++]);
            if(y2&1)ret=max(ret,tree[x][--y2]);
        }
        return ret;
	}
	// long long getsum(int x1, int y1, int x2, int y2) {
	// 	ll ret = 0;
    //     for(x1 += size, x2 += size+1; x1 < x2; x1>>=1,x2>>=1){
    //         if(x1&1)ret+=get1dsum(x1++,y1,y2);
    //         if(x2&1)ret+=get1dsum(--x2,y1,y2);
    //     }
    //     return ret;
		
	// }
	ll query(int x1, int y1, int x2, int y2){
		ll ret = 0;
        for(x1 += size, x2 += size+1; x1 < x2; x1>>=1,x2>>=1){
            if(x1&1)ret=max(ret,get1dquery(x1++,y1,y2));
            if(x2&1)ret=max(ret,get1dquery(--x2,y1,y2));
        }
        return ret;
	}
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c, d;
    cin >> N >> M;
	segtree2d seg(1502);
	vector<vector<ll>> v(1502,vector<ll>(1502));
	for(int i = 0;i  < N; i++){
		cin >> a >> b >> c >> d;
		
		v[a][b]++;
		v[a][d]--;
		v[c][b]--;
		v[c][d]++;
	}
	for(int i = 0;i <= 1500;i++){
		for(int j = 1; j <= 1500;j ++){
			v[i][j]+=v[i][j-1];
		}
	}
	for(int i = 0;i <= 1500;i++){
		for(int j = 1; j <= 1500;j ++){
			v[j][i]+=v[j-1][i];
		}
	}
	// for(int i = 6; i>=4; i--){
	// 	for(int j = 0; j <= 6; j++){
	// 		cout << v[i][j] << ' ';
	// 	}
	// 	cout << '\n';
	// }
	seg.init(v);
	for(int i = 0; i < M; i++){
		cin >> a >> b >> c >> d;
		
		
		cout << seg.query(a,b,c-1,d-1) << '\n';
	}
    
}