#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int K,N;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> K;
    vector<int> v(N);
    int r=1;
    for(int i = 0; i < N; i++){
        cin >> v[i];
        r+=v[i];
    }
    int l = 0;
    //[l,r)
    while(l+1<r){
        int mid = l+r>>1;
        int rnums=0;
        int tmp=0;
        for(int i = 0; i < N; i++){
            tmp+=v[i];
            if(tmp>=mid){
                tmp=0;
                rnums++;
            }
        }
        if(rnums<K){
            r=mid;
        }
        else {
            l=mid;
        }
    }
    cout << l;
}