#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int INF = 1e5;

ll N;
int len, K;
int digit[20];
string dp[1 << 11][19][2];

//breaking N down into individual digits
void digits()
{
    ll num = N;

    while (num)
    {
        digit[len++] = num % 10;
        num /= 10;
    }

    //swapping order
    for (int s = 0, e = len - 1; s < e; s++, e--)
    {
        int tmp = digit[s];
        digit[s] = digit[e];
        digit[e] = tmp;
    }
}

string sol(int idx, int taken, int takenCnt, int pass)
{
    if (idx == len)
        return takenCnt == K ? "" : "111111111111111111111111111111111";
        //cause an overflow(ret.size()>=30)if takenCnt is wrong
    string &ret = dp[taken][idx][pass];

    if (!ret.empty())
        return ret;

    for (int d = (pass == 1 ? (idx == 0) : digit[idx]); d < 10 + (idx == 0); d++)
    {
        int npass = pass || d > digit[idx];

        //has to pass
        if (d == 10)
        {
            len += 1;
            ret = to_string(1) + 
            sol(idx + 1, taken | (1 << 1), takenCnt + !(taken & (1 << 1)), 1);
            //!(taken & (1 << 1)) checks if we already had that bit enabled
        }
        else
        {
            ret = to_string(d) + 
            sol(idx + 1, taken | (1 << d), takenCnt + !(taken & (1 << d)), npass);
        }
        if(ret.size()<30)return ret;
    }
    return ret;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    int p = 0;
    digits();
    if (len < K)
    {
        len = K;
        p = 1;
    }
    cout << sol(0, 0, 0, p);
}