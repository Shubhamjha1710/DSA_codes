https://codeforces.com/blog/entry/83248

#include<vector>
#include<iostream>
#include<algorithm>
using namespace std; 
#define ll long long
// Sqrt Decomposition is a method (or a data structure) that allows you to perform some common operations (finding sum of the elements of the sub-array, finding the minimal/maximal element, etc.) in O(sqrt(n)) operations, which is much faster than O(n)for the trivial algorithm.

// 1 Given an array a[0 , n-1] , implement a data structure that allows to find the sum of the elements a[l, r] for arbitrary l and r in O(sqrt(n)) operations.

// approach
// a. The basic idea of sqrt decomposition is preprocessing. We'll divide the array a into blocks of length approximately sqrt(n), and for each block i we'll precalculate the sum of elements in it b[i].We can assume that both the size of the block and the number of blocks are equal to sqrt(n) rounded up: s = ceil(sqrt(n))
// so array a can be divided as a[0.....s-1] + a[s ...... 2s-1] + a[2s ....... 3s-1] + ... + a[(m-1)s.....ms-1]
// this can be represented as b[0] , b[1] , b[2] ..... b[m-1]
// b. now to calculate the sum of elements in subarray[l...r] there is two case
// 1. if (r-l+1) >= sqrt(n) then it will contain several blocks to find the sum of complete blocks we use precomputed b array to find the sum of tails we compute the array sum by naive approach
// 2. if (r-l+1) < sqrt(n) then the subarray size is part of a block we calculate the sum by using naively

// implementation
vector<ll> sqrt(vector<ll> &vt , ll n)
{
    ll len = sqrt(n)+1;
    vector<ll> b(len+1);
    for(ll i = 0; i < n; i++) b[i/len] += vt[i];

    ll q;
    cin >> q;
    for(ll i = 0; i < q; i++)
    {
        ll sum = 0;
        ll left, right;
        cin >> left >> right;
        for(ll j = left;j<=right;)
        {
            if(j%len == 0 && j+len-1 <= right) 
            {
                sum += b[j/len];
                j += len;
            }
            else
            {
                sum += vt[j];
                j+=1;
            }
        }
        cout << sum << endl;
    }
}

// If an element  a[i] changes, it's sufficient to update the value of b[k] for the block to which this element belongs k = i/s in one operation.
// b[k] += (vt[i]new - vt[i]old)
// we can also modify this sqrt in case of range update by adding lazy array to store an infomation about individual elemet updation


// 1. Mo's algorithm
// we will use mo algorithm when the merging of answer from different blocks is quite complex and time consuming
// Mo algorithm used to answer the offline queries, in these types of queries your array doesn't modify so you can rearrange the quries to make solution efficient
// time complexity = O((n+q)*sqrt(n)) (read https://www.geeksforgeeks.org/mos-algorithm-query-square-root-decomposition-set-1-introduction/)
// The idea is to answer the queries in a special order based on the indices. We will first answer all queries which have the left index in block 0, then answer all queries which have left index in block 1 and so on. And also we will have to answer the queries of a block is a special order, namely sorted by the right index of the queries. (so here we are sorting the queries by the left value) 
// We will use a single data structure. This data structure will store information about the range. At the beginning this range will be empty. When we want to answer the next query (in the special order), we simply extend or reduce the range, by adding/removing elements on both sides of the current range, until we transformed it into the query range. 

// instead of ussing 101 use sqrt(MAX_N)
// ques :- https://www.geeksforgeeks.org/problems/interesting-queries4742/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
static bool cmp(vector<int> &a, vector<int> &b)
{
    if(a[0]/101 != b[0]/101) return a[0]/101 < b[0]/101;
    else return a[1] < b[1];
}

vector<int> Mos_algorithm(vector<int>nums, vector<vector<int>> Queries, int k)
{
    int n = nums.size();
    int q = Queries.size();
    for(int i = 0;i<q;i++) Queries[i].push_back(i);
    sort(Queries.begin(), Queries.end() , cmp);
    
    // mainly this Mos algrithm
    int mp[1001] = {0};
    int left = 0 , right = -1 , cnt = 0;  // if 0 based index
    // int left = 0 , right = 0 , cnt = 0;   if 1 based index

    // here our window is [left , right] 
    vector<int> ans(q , 0);
    for(int i = 0;i<q;i++)
    {
        // always write the element adding ways first
        while(left > Queries[i][0]) // adding element in range
        {
            left-=1;
            mp[nums[left]]+=1;
            if(mp[nums[left]] == k) cnt+=1;
            // add_element();
        }
        while(right < Queries[i][1]) // adding element in range
        {
            right+=1;
            mp[nums[right]]+=1;
            if(mp[nums[right]] == k) cnt+=1;
            // add_element();
        }
        while(left < Queries[i][0]) // removing element from range
        {
            // remove_element();
            mp[nums[left]]-=1;
            if(mp[nums[left]] == k-1) cnt-=1;
            left+=1;
        }
        while(right > Queries[i][1]) // removing element from range
        {
            // remove_element();
            mp[nums[right]]-=1;
            if(mp[nums[right]] == k-1) cnt-=1;
            right-=1;
        }
        ans[Queries[i][2]] = cnt;
    }
    return ans;
}

// 2. Heavy Light Nodes
https://codeforces.com/contest/398/problem/D
// A nodes is said to heavy node if degree of node U is greater than value C and it is light node if degree is less than C
// This value of C is optimally defined such as C = sqrt(n)
// So to find the query on light node we find is by brute force by iterating all its neighbhour, while for heavy node we have answer stored in a data structure which gives ans in constant time or logn time


// 3. 