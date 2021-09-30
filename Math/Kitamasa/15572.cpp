#include <bits/stdc++.h>

using namespace std;

using ll = long long;
ll N, M;
const int MOD = 1999;
//terms and coefficients
vector<ll> a,c;

//C(n,*)->C(n+1,*)
void next(ll k, vector<ll>& c0, vector<ll>& c1){
    //assuming all vectors are of size k
    c1[0]=(c0[k-1]*c[0])%MOD;
    for (int i = 1; i < k; i++) {
		c1[i] = (c0[i - 1] + c0[k - 1] * c[i]) % MOD;
	}
}

//C(n,*)->C(2n,*)
void dbl(ll k, vector<ll>& c0, vector<ll>& c1) {
    vector<vector<ll>> cs(k,vector<ll>(k));
	for (int i = 0; i < k; i++) {
		cs[0][i] = c0[i];
	}
	for (int i = 0; i < k - 1; i++) {
		next(k, cs[i], cs[i + 1]);
	}
	for (int i = 0; i < k; i++) {
		c1[i] = 0;
		for (int j = 0; j < k; j++) {
			c1[i] += cs[0][j] * cs[j][i];
			c1[i] %= MOD;
		}
	}
}

//calculating a_m from previous linear combinations(a,c)
ll kitamasa(ll m, ll k){
    if(m==0)return a[0];
    vector<ll> c0(k),c1(k);
    for(int i = 0; i < k; i++){
        c0[i]=0;
    }
    c0[1]=1;
    //starting with C(0,*) to create C(M,*)
    //first we find the msb of m
    int p = 62;
    while(((m>>--p)&1)==0);
    //then we calculate C(M,*)
    while(p-->0){
        dbl(k,c0,c0);
        if((m>>p)&1){
            next(k,c0,c1);
            for(int j = 0; j < k; j++){
                c0[j]=c1[j];
            }
        }
    }

    //now we calculate a_m
    ll ret = 0;
    for(int i = 0; i < k; i++){
        ret+=(c0[i]*a[i])%MOD;
        ret%=MOD;
    }
    return ret;
}

//a_m = 
//  2^(M-1) (M<N)
//  2^N-1   (M=N)
//  a_(m-1) + a_(m-2) + ... + a_(m-n+1) + 2^(n-1) * a_(m-n) (M>N)

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    a=vector<ll>(N);
    c=vector<ll>(N);
    if(N==1){
        cout << 1;
        return 0;
    }

    //c = {2^(N-1), 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,11,1,1,1,1,1,1,1,1,,}
    for(int i = 0; i < N; i++){
        c[i]=1;
    }
    for(int i = 0; i < N-1; i++){
        c[0] = (c[0]*2)%MOD;
    }

    //a={1,2,4,8,...good}
    a[0]=1;
    for(int i = 1; i < N; i++){
        a[i]=(a[i-1]*2)%MOD;
    }
    //because of the exception case at M==N a_m = 2^N-1
    a[N-1]=(a[N-1]*2-1)%MOD;

    cout << kitamasa(M-1, N);

}