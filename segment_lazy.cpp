// lazy propagation is used when there is an update for whole range not a single index
// here like to find the sum for subsegment by query [l,r] and update the all element in range [l,r] 

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
    segment[segPos] = segment[2*segPos+1]+segment[2*segPos+2];
}

int query(vector<int> &segment , vector<int> &lazy, int q_left , int q_right , int r_left , int r_right , int segPos)
{
    if(lazy[segPos] != 0)
    {
        int dx = lazy[segPos];
        lazy[segPos] = 0;
        segment[segPos] += dx*(r_right-r_left+1);

        if(r_left != r_right)
        {
            lazy[2*segPos+1]+=dx;
            lazy[2*segPos+2]+=dx;
        }
    }

    if(q_left > r_right || q_right < r_left) return 0;
    if(q_left <= r_left && q_right >= r_right) return segment[segPos];

    int ans = 0;
    int mid = (r_left+r_right)/2;
    ans += query(segment , lazy , q_left , q_right , r_left , mid , 2*segPos+1);
    ans += query(segment , lazy , q_left , q_right , mid+1 , r_right , 2*segPos+2);
    return ans;
}

void update(vector<int> &segment , vector<int> &lazy , int q_left , int q_right , int r_left , int r_right ,int segPos , int val)
{
    if(lazy[segPos] != 0)
    {
        int dx = lazy[segPos];
        lazy[segPos] = 0;
        segment[segPos] += dx*(r_right-r_left+1);

        if(r_left != r_right)
        {
            lazy[2*segPos+1]+=dx;
            lazy[2*segPos+2]+=dx;
        }
    }

    if(q_left > r_right || q_right < r_left) return;
    if(q_left <= r_left && q_right >= r_right) 
    {
        int dx = val*(r_right-r_left+1);
        segment[segPos]+=dx;

        if(r_left != r_right)
        {
            lazy[2*segPos+1]+=val;
            lazy[2*segPos+2]+=val;
        }
        return;
    }

    int mid = (r_left + r_right)/2;
    update(segment , lazy , q_left, q_right , r_left, mid , 2*segPos+1 , val);
    update(segment , lazy , q_left, q_right , mid+1, r_right , 2*segPos+2 , val);
    segment[segPos] = segment[2*segPos+1] + segment[2*segPos+2];
}

int main()
{
    int n = 6;
    vector<int> vt = {-9,2,4,6,7,9};
    vector<int> segment(24 , 0);
    vector<int> lazy(24 , 0);
    construct_Tree(vt , segment , 0 , n-1 , 0 , n);

    cout << query(segment , lazy , 1 , 4 , 0 , n-1 , 0) << endl;
    cout << query(segment , lazy , 2 , 5 , 0 , n-1 , 0) << endl;
    update(segment , lazy , 2 , 5, 0 , n-1 , 0 , 5);
    cout << query(segment , lazy , 2 , 5 , 0 , n-1 , 0) << endl;
    update(segment , lazy , 3 , 4, 0 , n-1 , 0 , 5);
    cout << query(segment , lazy , 0 , 5 , 0 , n-1 , 0) << endl;
    return 0;
}