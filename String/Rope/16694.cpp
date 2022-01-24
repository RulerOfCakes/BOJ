#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    __gnu_cxx::rope<char> rp;
    string s;
    cin>>s;
    int N = s.size();
    rp.append(s.c_str());
    int Q;
    cin>>Q;
    while(Q--){
        int a,b,c;
        cin>>a>>b;
        if(a==3){
            cout << rp.at(b) << '\n';
        }
        else{
            cin>>c;
            if(a==1){
                rp=rp.substr(b,c-b+1)+rp.substr(0,b)+rp.substr(c+1,N-c);
            }
            else{
                rp=rp.substr(0,b)+rp.substr(c+1,N-c)+rp.substr(b,c-b+1);
            }
        }
    }
}