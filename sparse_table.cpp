#include <bits/stdc++.h>
using namespace std;
#define ll long long
// Sparse Table is a data structure, that allows answering range queries. It can answer most range queries in O(log n), but its true power is answering range minimum queries (or equivalent range maximum queries). For those queries it can compute the answer in O(1) time.
// The only drawback of this data structure is, that it can only be used on immutable arrays. This means, that the array cannot be changed between two queries. If any element in the array changes, the complete data structure has to be recomputed.

// Intuition
// Any non-negative number can be uniquely represented as a sum of decreasing powers of two. 
// By the same reasoning any interval can be uniquely represented as a union of intervals with lengths that are decreasing powers of two. E.g. [2, 14] = [2, 9] + [10, 13] + [14, 14]
// This break down of ranges in shorter range in term of power of two takes O(log(n)) time
// The main idea behind Sparse Tables is to precompute all answers for range queries with power of two length. Afterwards a different range query can be answered by splitting the range into ranges with power of two lengths


// use 2d matrix where vt[i][j] :- store the maximum value of (or ans) for range [i,i+(1<<j)-1] means range of length (1<<j)
// so dimension of 2d matrix is n*(log2(max value of n))
// space complexity = O(30*n) when n <= 1e9
// time complexity = O(nlogn) for each query of logn

// filling sparse table
vector<vector<ll>> sparse_table(vector<ll> &vt , ll n)
{
    vector<vector<ll>> aux(n , vector<ll>(30 , -1));
    for(ll i = 0; i < n; i++) aux[i][0] = vt[i]
    for(ll j = 1;j<30;j++)
    {
        for(ll i = 0; i < n; i++) 
        {
            if(i+(1<<(j-1)) < n) aux[i][j] = max(aux[i][j-1], aux[i+(1<<(j-1))][j-1]);
            // for sum it should be aux[i][j] = (aux[i][j-1] + aux[i+(1<<(j-1))][j-1]);
        }
    }
}

// finding the minimum from range [l...r] in logn time
ll find_min(vector<vector<ll>> &aux , ll left , ll right)
{
    ll ans = 0;
    ll len = (rigth-left+1);
    for(ll i = 29;i>=0;i--)
    {
        if((len&(1<<i)))
        {
            ans = max(ans , aux[left][i]);
            left = left+(1<<i);
        }
    }
    return ans;
}

// find the minimum from range [l....r] in O(1) time
// this method only work for idempotent functions where (a func a) = a
// this func may be & , | , max , min
ll find_min(vector<vector<ll>> &aux , ll left , ll right)
{
    ll ln = log(right-left+1);
    return min(aux[left][ln] , aux[right - (1<<ln)+1][ln]);

    // working let says there is range [l.........r]
    // now ln = log(r-l+1) give some value of ln such that (1<<ln) <= (r-l+1)
    // this give aux two ranges [left ... left +(1<<ln1)-1] and [right-(1<<ln)+1 ... right] 
    // i.e aux[left][ln] and aux[right-(1<<ln)+1][ln]
}