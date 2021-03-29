#include <bits/stdc++.h>

using namespace std;
using base = complex<double>;
int N;
vector<int> v;
void fft(){
    if(v.size()==1)return;

    vector<base> w;
    for(int i = 0; i <= N/2; i++){
        w.push_back(exp(imag(2)*M_PI*i/N));
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    
}