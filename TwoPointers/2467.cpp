#include <bits/stdc++.h>
using namespace std;
int N;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    vector<int> v(N);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    int l = 0,r = N-1;
    int a1,a2,ans=2e9;
    while(l<r){
        int sum = v[l]+v[r];
        if(abs(sum)<ans){
            ans=abs(sum);
            a1=v[l];
            a2=v[r];
        }
        if(sum<0){
            l++;
        }
        else if(sum>0) r--;
        else{
            a1=v[l];
            a2=v[r];
            break;
        }
    }
    cout << a1 << ' ' << a2;
}