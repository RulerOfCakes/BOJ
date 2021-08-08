#include <bits/stdc++.h>

using namespace std;

int T, N;

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N;
        vector<int> arr(N + 1, 0);

        for (int i = 0; i < N; i++)
        {
            cin >> arr[i + 1];
        }
        int ans = 0;
        for (int i = 1; i <= N; i++)
        {
            vector<int> dp(1, -1);
            for (int j = i; j <= N; j++)
            {

                if (dp.back() < arr[j])
                    dp.push_back(arr[j]);
                else
                    *lower_bound(dp.begin(), dp.end(), arr[j]) = arr[j];

                ans += dp.size() - 1;
            }
        }
        cout << "Case #" << t << ": " << ans << '\n';
    }
}