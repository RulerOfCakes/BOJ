#include <bits/stdc++.h>

using namespace std;

int N;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    bool flip = 0;
    while(N){
        if(N-3 > 0)N -= 3;
        else N--;

        if(!N){
            if(!flip){
                cout << "CY";
            }
            else{
                cout << "SK";
            }
        }
        flip = !flip;
    }
}