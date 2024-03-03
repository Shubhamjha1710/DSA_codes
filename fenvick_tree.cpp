#include <bits/stdc++.h>
using namespace std;
#define M 1000000007
#define endl "\n"
#define ll long long
#define lld long double
#define vi vector<int>
#define vll vector<ll>
#define mx 1e18
#define mn INT_MIN

// when bit[200001] store the sum of whole array
// here get_sum(idx) gives sum from [0,idx];

class BIT
{
    public:
    vector<int> arr;
    BIT()
    {
        arr.resize(100001);
    }

    void update(int idx)
    {
        if (idx == 0)
        {
            bit[idx] += 1;
            return;
        }
        while (idx <= 100000)
        {
            arr[idx] += 1;
            idx += (idx & (-idx));
        }
    }

    int sum(int idx)
    {
        int ans = bit[0];
        while (idx)
        {
            ans += arr[idx];
            idx -= (idx & (-idx));
        }
        return ans;
    }
};





void update(vector<ll> &bit, ll idx)
{
    if (idx == 0)
    {
        bit[idx] += 1;
        return;
    }
    while (idx <= 200000)
    {
        bit[idx] += 1;
        idx += (idx & (-idx));
    }
}

ll get_sum(vector<ll> &bit, ll idx)
{
    ll sum = 0;
    while (idx)
    {
        sum += bit[idx];
        idx -= (idx & (-idx));
    }
    sum += bit[idx];
    return sum;
}
// ll sum = get_sum(bit , 200000) - get_sum(bit , idx)

// when bit[0] store the complete sum;
// here get_sum(idx) give sum from [idx , 200000]
void update(vector<ll> &bit, ll idx)
{
    while (idx)
    {
        bit[idx] += 1;
        idx -= (idx & (-idx));
    }
    bit[0] += 1;
}

void get_sum(vector<ll> &bit, ll idx)
{
    ll sum = 0;
    if (idx == 0)
        return bit[0];
    while (idx <= 200000)
    {
        sum += bit[idx] idx += (idx & (-idx));
    }
    return sum
}
// ll sum = get_sum(bit , 0) - get_sum(bit , idx)