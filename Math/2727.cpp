#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;
vector<pi>ans;
vector<int> pow3;

int sol(int N, int pow){
    if(!N)return 0;
    if(N==1){
        ans.push_back({0,0});
        return 1;
    }
    if(N%2==0){
        int ret = sol(N/2,pow);
        for(int i = pow; i < pow+ret; i++){
            ans[i].first++;
        }
        return ret;
    }
    else{
        int p3 = (upper_bound(pow3.begin(),pow3.end(),N)-1)-pow3.begin();
        
        ans.push_back({0,p3});
        int ret = sol(N-pow3[p3], pow+1)+1;
        return ret;
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N;
    cin>>N;
    pow3=vector<int>(20);
    pow3[0]=1;
    for(int i = 1; i < 20; i++){
        pow3[i]=pow3[i-1]*3;
    }
    while(N--){
        int A;
        cin >> A;
        ans=vector<pi>();
        cout << sol(A,0) << '\n';
        for(auto a : ans){
            cout << a.first << ' ' << a.second << '\n';
        }
    }
}