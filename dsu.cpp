// Disjoint Set Union
// this will use ackermann fucntion
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll find(vector<ll> &dsu , ll a)
{
    if(dsu[a] == a) return a;
    return dsu[a] = find(dsu, dsu[a]);
}

void unions(vector<ll> &dsu , vector<ll> &rank, ll a , ll b)
{
    a = find(dsu , a);
    b = find(dsu , b);

    if (a != b) 
    {
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        rank[a] += rank[b];
    }

}

// DSU Modifications

// 1. Weighted DSU (watch vivek gupta video)
// In previous union find each edges has same weights so this is easy to implement (usefull when the we have to find the number of connected components)
// But here we also consider the case when each edges has its own weights
// dsu[i].first : stores the leader of i 
// dsu[i].second : stores the distance from that leader
// find(x) :- gives the leader of x and distance of x from that leader pair<leader , dist>

pair<ll, ll> find(vector<pair<ll , ll>> &dsu , ll a) 
{
    if(a != dsu[a].first) 
    {
        ll len = dsu[a].second;
        dsu[a] = find_set(dsu , dsu[v].first);
        dsu[a].second += len;
    }
    return dsu[a];
}


// means add an edge from a to b 
void union_sets(ll a, ll b , ll dist) 
{
    ll root1 = find_set(a).first;
    ll root2 = find_set(b).first;
    if (root1 != root2) // means in different set
    {
        if(rank[root1] < rank[root2]) swap(root1, root2);

        ll len =  find_set(a).second - dist - find_set(b).second;
        dsu[root2] = make_pair(root1, len);
        if(rank[root1] == rank[root2]) rank[root1]+=1; // rank hai not size
    }
    else // in same set , so check for consistency
}

// Dsu Rollbacks 
// Rollbacks in Dsu is complex when you are using path compression with dsu because of large change occurs in dsu it is in effecient to store all that changes
// So only use rank compression, dont use the path compression then time complexity of union find is logn which is pretty good so store all merging history inside a stack and pop back current top of stack and rollback to previous version 
// store <leader , previous parent , rank of leader> in stack
// and make dsu[leader] = previous parent and rank[leader] = rank of leader and pop stack top, in most cases leader = previous parent 

ll find(vector<ll> &dsu , ll a)
{
    if(dsu[a] == a) return a;
    return find(dsu, dsu[a]); // no path compression
}

void unions(vector<ll> &dsu , vector<ll> &rank , stack<pair<ll,ll>> &st , ll a , ll b)
{
    a = find(dsu , a);
    b = find(dsu , b);

    if (a != b) 
    {
        if (rank[a] < rank[b]) swap(a, b);
        st.push({b , rank[b]});
        parent[b] = a;
        rank[a] += rank[b];
    }
}

void rollback(vector<ll> &dsu , vector<ll> &ranks , stack<pair<ll ,ll>> &st)
{
    ll initial = st.top().first;
    ll initial_rank = st.top().second;
    rank[find(dsu , initial)]-=initial[rank];

    st.pop();

    dsu[initial] = initial;
    rank[inital] = initial_rank;
}


// Dsu on Tree