#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N;cin>>N;
    int res1,res2;
    cout << "? 1" << endl;
    cin >> res1;
    cout << "? " << N << endl;
    cin >> res2;
    cout << "! ";
    if(res1==res2){
        cout << 0 << endl;
    }
    else if(res1<res2){
        cout << 1 << endl;
    }
    else{
        cout << -1 << endl;
    }
    return 0;
}