#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<long long, long long>;

int N, M, K;
const int INF = 1e9 + 7;
vector<pi> v;
vector<pi> A, B;
int ccw(pi p1, pi p2)
{
    long long ret = p1.first * p2.second - p2.first * p1.second;
    if (ret < 0)
        return -1;
    else if (ret > 0)
        return 1;
    else
        return 0;
}

int ccw(pi p1, pi p2, pi p3)
{
    return ccw({p1.first - p3.first, p1.second - p3.second}, {p2.first - p3.first, p2.second - p3.second});
}

bool checker(vector<pi> &C, vector<double> &Ctan, ll x, ll y)
{
    if (x <= C[0].first)
        return false;
    double tan = ((double)y - C[0].second) / ((double)x - C[0].first);
    if (Ctan[1] > tan || Ctan[N - 1] < tan)
        return false;

    int left = 1, right = N - 1, mid, idx = 1;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (tan == Ctan[mid])
        {
            if (x < C[mid].first)
                return true;
            else
                return false;
        }
        else if (tan > Ctan[mid])
        {
            left = mid + 1;
            idx = mid;
        }
        else
        {
            right = mid - 1;
        }
    }
    //if inside they all have to be ccw
    if (ccw({x, y}, C[0], C[idx]) != 1)
        return false;
    else if (ccw({x, y}, C[idx], C[idx + 1]) != 1)
        return false;
    else if (ccw({x, y}, C[idx + 1], C[0]) != 1)
        return false;
    return true;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<pi> At, Bt;
    cin >> N >> M >> K;
    int idx = -1;
    ll x = INT_MAX, y = INT_MAX;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        At.push_back({a, b});
        if (x > a)
        {
            idx = i;
            y = b;
            x = a;
        }
    }
    for (int i = idx; i < idx + N; i++)
    {
        A.push_back(At[i % N]);
    }
    idx = -1;
    x = INT_MAX;
    y = INT_MAX;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        Bt.push_back({a, b});
        if (x > a)
        {
            idx = i;
            y = b;
            x = a;
        }
    }
    for (int i = idx; i < idx + M; i++)
    {
        B.push_back(Bt[i % M]);
    }
    //vector of tangents
    vector<double> Atan(N + 1), Btan(N + 1);

    for (int i = 1; i < N; i++)
    {
        if (A[i].first == A[0].first)
        {
            Atan[i] = A[i].second > A[0].second ? INF : -INF;
        }
        else
        {
            Atan[i] = ((double)A[i].second - A[0].second) / ((double)A[i].first - A[0].first);
        }
    }
    for (int i = 1; i < M; i++)
    {
        if (B[i].first == B[0].first)
        {
            Btan[i] = B[i].second > B[0].second ? INF : -INF;
        }
        else
        {
            Btan[i] = ((double)B[i].second - B[0].second) / ((double)B[i].first - B[0].first);
        }
    }
    int ans = 0;

    while (K--)
    {
        cin >> x >> y;
        if (!checker(A, Atan, x, y))
            ans++;
        else if (checker(B, Btan, x, y))
            ans++;
    }
    if (!ans)
    {
        cout << "YES";
    }
    else
        cout << ans;
}