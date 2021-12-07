#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int,int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    string s;
    cin>>s;
    vector<char> v;
    for(int i = 0; i < s.length(); i++){
        v.push_back(s[i]);
        if(s[i]=='P'&&v.size()>=4){
            int k = v.size()-1;
            if((v[k-3]=='P')&&(v[k-2]=='P')&&(v[k-1]=='A')&&(v[k]=='P')){
                for(int j = 0; j < 3; j++){
                    v.pop_back();
                }
            }
        }
    }
    if(v.size()==1&&v[0]=='P'){
        cout << "PPAP";
    }
    else{
        cout << "NP";
    }
}