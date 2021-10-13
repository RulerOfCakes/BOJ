#include <bits/stdc++.h>

using namespace std;
int N;
string s1, s2;
int pi[1000002];
int cnt;
void getPi(){
    int n = s2.length();
    for(int i = 1, mat=  0; i < n; ++i){
        if(s2[i] == s2[mat]){
            pi[i] = ++mat;
        } else if(mat != 0){
            --i;
            mat = pi[mat-1];
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while(true){
        cin >> s2;
        if(s2==".")break;
        memset(pi,0,sizeof(pi));
        getPi();
        if(s2.length()%(s2.length()-pi[s2.length()-1])==0)cout << s2.length()/(s2.length()-pi[s2.length()-1])<<'\n';
        else cout << 1 << '\n';
    }
}