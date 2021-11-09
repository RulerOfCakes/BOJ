#include <bits/stdc++.h>
using namespace std;
int N;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    vector<int> cnt(10);
    string s;
    cin>>s;
    for(char c: s){
        if(c-'0'==9)cnt[6]++;
        else
            cnt[c-'0']++;
    }
    int ans = 0;
    while(true){
        ans++;
        bool cmp=1;
        for(int i = 0; i <=8; i++){
            if(cnt[i]==0)continue;
            if(i==6){
                cnt[i]-=2;
                if(cnt[i]<0)cnt[i]=0;
            }
            else
                cnt[i]--;
            if(cnt[i]!=0)cmp=0;
        }
        if(cmp)break;
    }
    cout << ans;
}