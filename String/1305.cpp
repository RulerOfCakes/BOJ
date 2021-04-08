#include <bits/stdc++.h>

using namespace std;
int N;
string s2;
int pi[1000001];

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
    cin >> N;
    cin >> s2;
    getPi();
    
    cout << N-pi[N-1];
}