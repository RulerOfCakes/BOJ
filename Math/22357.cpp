#include <bits/stdc++.h>

using namespace std;

int N, K;
bool prime[100002];


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> K >> N;
    vector<int> primes;
    for(int i = 2; i <= 100000; i++){
        if(!prime[i]){
            if(i>=N){
            primes.push_back(i);
            if(primes.size()>=K)break;
            }
            for(int j = 2 * i; j <= 100000; j += i){
                prime[j] = 1;
            }
        }
    }
    for(int i = 0; i < K; i++){
        for(int j = 0; j < N; j++){
            cout << primes[i]*(j+1) << ' ';
        }
        cout << '\n';
    }
    
}