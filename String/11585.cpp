#include <bits/stdc++.h>

using namespace std;
int N;
string s1, s2;
int pi[2000002];
int res[2000002];
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

int gcd(int a, int b){
    if(b==0)return a;
    return gcd(b,a%b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        char c;
        cin >> c;
        s2.push_back(c);
    }
    for(int i = 0; i < N; i++){
        char c; cin >> c;
        s1.push_back(c);
    }
    s1+=s1;
    s1.pop_back();
    getPi();
    kmp();
    int cd = gcd(cnt,N);
    cout << cnt/cd << '/' << N/cd << '\n';
    
}