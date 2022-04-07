#include <bits/stdc++.h>
using namespace std; 
using ll = long long;
const int MOD = 20200429;

ll mul(ll x, int cnt){
    if(!cnt)return 1;
    else if(cnt==1)return x;

    ll n = mul(x,cnt/2);
    if(cnt%2)return (((n*n)%MOD)*x)%MOD;
    else return (n*n)%MOD;
}
vector<ll> rv;vector<char>iv;
    int y = 20200402;

string sol(string cs, ll val){
    //cout << cs << endl;
    if(val==y){
        cout << cs << endl;
        return cs;
    }
    else if(cs.length()>=6)return "";
    string ret;
    for(int i = 0;i < iv.size(); i++){
        if(!ret.empty())return ret;
        string ins = cs+iv[i];
        string tmp = sol(ins,(val+rv[i])%MOD);
        if(tmp.empty())continue;
        ret=tmp;
    }
    return ret;
}

int main(){
    for(char i = 48; i <= 57; i++)iv.push_back(i);
    for(char i = 65; i <= 90; i++)iv.push_back(i);
    for(char i = 97; i <= 122; i++)iv.push_back(i);

    for(char c : iv)
        rv.push_back(mul(c,814));
    // cout << "HA" << endl;
    string ans = "";
    ll cret = 0;

    cout << sol(ans, 0);
}