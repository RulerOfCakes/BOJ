#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll psum[101010];
ll qsum[101010];
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,Q;
    cin >> N >> Q;
    
    for(int i = 1; i <= N; i++){
        int a;
        cin >> a;
        psum[i]=psum[i-1]+a;
        qsum[i]=qsum[i-1]+a*a;
    }
    while(Q--){
        int l,r;
        cin >> l >> r;
        cout << ((psum[r]-psum[l-1])*(psum[r]-psum[l-1])-(qsum[r]-qsum[l-1]))/2 << '\n';
    }
}