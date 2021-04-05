#include <bits/stdc++.h>

using namespace std;
int N;
string arr[1002];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string s;
    cin >> s;
    for(int i = 0; i < s.length(); i++){
        arr[i] = s.substr(i);
    }
    sort(arr, arr+s.length());
    for(int i = 0 ; i < s.length(); i++){
        cout << arr[i] << '\n';
    }
    
}