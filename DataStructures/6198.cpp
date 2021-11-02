#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N;
    cin >> N;
    stack<int> s;
    ll ans=0;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        while(!s.empty()&&s.top()<=a){
            s.pop();
        }
        ans+=s.size();
        s.push(a);
    }
    cout << ans;
}