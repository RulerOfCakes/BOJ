#include <bits/stdc++.h>
using namespace std;
int N;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;vector<int>v(N);
    for(int i = 0; i < N; i++)
        cin>>v[i];
    int l = 0,r=N-1,ans=INT_MAX;
    while(l<r){
        int tmp=v[l]+v[r];
        if(abs(tmp)<abs(ans))ans=tmp;
        if(tmp<0){
            l++;
        }
        else if(tmp>0){
            r--;
        }
        else break;
    }
    cout << ans;
}