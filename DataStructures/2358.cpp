#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

int N;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    vector<int> xansidx;
    vector<int> yansidx;
    map<int, int> xmp;
    map<int ,int> ymp;
    for(int i = 0;i  < N; i++){
        int a, b;
        cin >> a >> b;
        if(xmp.find(a)==xmp.end()){
            xmp[a]=1;
            xansidx.push_back(a);
        }
        else{
            xmp[a]++;
        }
        if(ymp.find(b)==ymp.end()){
            ymp[b]=1;
            yansidx.push_back(b);
        }
        else{
            ymp[b]++;
        }
    }
    ll ans = 0;
    for(int ai : xansidx){
        int a = xmp[ai];
        ans+=a>1?1:0;
    }
    for(int bi : yansidx){
        int b = ymp[bi];
        ans+=b>1?1:0;
    }
    cout << ans;
}