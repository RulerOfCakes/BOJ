#include <bits/stdc++.h>
using namespace std;
int N,M;
bool prime[1010101];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    vector<int> primes;
    for(int i = 2; i < 1010101; i++){
        if(!prime[i]){
            primes.push_back(i);
            for(int j = i*2; j < 1010101; j+=i){
                prime[j]=1;
            }
        }
    }
    cin>>N;
    while(N){
        int p1,p2=-1;
        for(int x : primes){
            p1=x;
            if(!prime[N-p1]){
                p2=N-p1;break;
            }
        }
        if(p2!=-1)
            cout << N << " = " << p1 << " + " << p2 << '\n';
        else{
            cout << "Goldbach's conjecture is wrong.\n";
        }
        cin>>N;
    }
}