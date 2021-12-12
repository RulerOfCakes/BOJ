#include <bits/stdc++.h>
using namespace std;
int N,M,K,T;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> T;
    while(T--){
        cin >> N >> M >> K;
        if(2*K>M)cout << "Yuto";
        else if((N*M-K*K*2)%2)cout << "Yuto";
        else cout << "Platina";
        cout << '\n';
    }
}