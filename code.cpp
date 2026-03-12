/*
Climbing Stairs:
-You are climbing a staircase. It takes n steps to reach the top.
-Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top
Example:
5:
    1+1+1+1+1
    1+1+1+2
    1+1+2+1
    1+2+1+1
    2+1+1+1
    1+2+2
    2+1+2
    2+2+1
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout << "Enter number of steps : ";
    cin >> n;

    int dp[n + 1];
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    cout << "Number of ways to climb stairs : " << dp[n];

    return 0;
}
