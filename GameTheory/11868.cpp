#include <bits/stdc++.h>
using namespace std;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    int ans = 0;
    while (N--)
    {
        int a;
        cin >> a;
        ans ^= a;
    }
    if (ans)
        cout << "koosaga";
    else
        cout << "cubelover";
}