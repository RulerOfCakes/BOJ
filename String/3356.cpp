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
    cin.tie(0)->sync_with_stdio(0);
    
    cin>>N>>s2;
    getPi();
    cout << N-pi[N-1];
}