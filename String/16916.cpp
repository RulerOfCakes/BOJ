#include <bits/stdc++.h>

using namespace std;
int N;
string s1, s2;
int pi[1000001];
int res[1000001];
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
void kmp(){
    int n = s1.length(), m = s2.length();
    //i: index, mat: number of matches
    for(int i = 0, mat = 0; i < n; i++){
        if(s1[i]==s2[mat]){
            if(++mat==m){
                res[cnt++] = i-m+1;
                mat=pi[mat-1];
            }
        }
        else if (mat != 0){
            --i;
            mat = pi[mat-1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    getline(cin, s1);
    getline(cin, s2);
    getPi();
    kmp();
    cout << (cnt>0?1:0) << '\n';
    
}