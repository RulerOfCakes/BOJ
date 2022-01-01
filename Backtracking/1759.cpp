#include <bits/stdc++.h>

using namespace std;
int L,C;
vector<char> v;
vector<string> ans;
bool mo[102];

void sol(int idx, int vow, int con, string s){
    if(s.length()==L){
        if(vow>=1&&con>=2)ans.push_back(s);
        return;
    }
    if(idx>=C)return;
    for(int i = idx; i < v.size(); i++){
        string ts=s+v[i];
        sol(i+1,vow+mo[v[i]-'a'],con+!mo[v[i]-'a'],ts);
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> L>>C;
    v.resize(C);
    mo['a'-'a']=1;
    mo['e'-'a']=1;
    mo['i'-'a']=1;
    mo['o'-'a']=1;
    mo['u'-'a']=1;
    for(int i = 0; i < C; i++){
        cin >> v[i];
    }
    sort(v.begin(),v.end());
    sol(0,0,0,"");
    for(string s : ans){
        cout << s << '\n';
    }
}