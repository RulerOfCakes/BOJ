#include <bits/stdc++.h>

using namespace std;
using ll = long long;

string X, Y;

int lcs(int i, int j){
    if(i==0||j==0){
        return 0;
    }
    if(X[i]==Y[j]){
        return lcs(i-1, j-1)+1;
    }
    else{
        return max(lcs(i-1, j), lcs(i, j-1));
    }
}

int lcsprime(int i, int j){
    if(i==X.length()||j==Y.length())return 0;
    if(X[i] == Y[j]){
        return lcsprime(i+1, j+1)+1;
    }
    else{
        return max(lcsprime(i+1, j), lcsprime(i, j+1));
    }
}

int LCS(){
    int maxx = 0;
    for(int l = 0; l <= Y.length(); l++)
    maxx = max(maxx, (lcs(X.length()/2, l) + lcsprime(X.length()/2+1, l+1)));
    return maxx;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> X;
    cin >> Y;
    if(X.length() < Y.length())swap(X, Y);
    cout << LCS();
} 