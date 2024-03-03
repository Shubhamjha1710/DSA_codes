// segment tree is a binary tree , where leaves nodes represent the element of given array
// segment tree is used to answer the query range questions
// In segment tree each node store the ans for some subarray 
// there is kinds of condition 
// 1. partial overlap (check for both right and left subtree)
// 2. complete overlap(stop here , store this as one of partial ans)
// 3. no overlap (stop here , this do not make contribution in our answer)

// no of nodes in segment tree = pow(2 , ceil(log2(n))+1)-1
// for right child : 2*i+1 
// for left child : 2*i+2
// for parent : (i-1)/2


// find the minimum in range [l...r]
#include <bits/stdc++.h>
using namespace std;
void construct_Tree(vector<int> &vt , vector<int> &segment , int low , int high , int segPos , int n)
{
    if(low == high)
    {
        segment[segPos] = vt[low];
        return;
    }

    int mid = (low+high)/2;
    construct_Tree(vt , segment , low , mid , 2*segPos+1 , n);
    construct_Tree(vt , segment , mid+1 , high , 2*segPos+2 , n);
    segment[segPos] = min(segment[2*segPos+1] , segment[2*segPos+2]);
}

int minRangeQuery(vector<int> &segment , int q_left , int q_right , int r_left , int r_right , int segPos)
{
    cout << r_left << " " << r_right << " " << segPos  << endl;
    // total_overlap
    if(q_left <= r_left && q_right >= r_right) return segment[segPos];
    // no overlap
    if(q_left > r_right || q_right < r_left) return INT_MAX;
    int mid = (r_left+r_right)/2;
    int ans = INT_MAX;
    ans = min(ans , minRangeQuery(segment , q_left , q_right , r_left , mid , 2*segPos+1));
    ans = min(ans , minRangeQuery(segment , q_left , q_right , mid+1 , r_right , 2*segPos+2));
    return ans;
}

void update(vector<int> &vt , vector<int> &segment , int low , int high , int segPos , int update_pos , int new_val)
{
    if(low == high)
    {
        segment[segPos] = new_val;
        return;
    }
    int mid = (low+high)/2;
    if(update_pos <= mid) 
        update(vt , segment , low , mid , 2*segPos+1 , update_pos , new_val);
    else 
        update(vt , segment , mid+1 , high , 2*segPos+2 , update_pos , new_val);
    segment[segPos] = min(segment[2*segPos+1], segment[2*segPos+2]);
}

int main()
{
    int n = 6;
    vector<int> vt = {-9,2,4,6,7,9};
    vector<int> segment(16 , INT_MAX);
    construct_Tree(vt , segment , 0 , n-1 , 0 , n);

    cout << minRangeQuery(segment , 5 ,5 , 0 , n-1 , 0) << endl;
    return 0;
}