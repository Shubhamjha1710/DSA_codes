// 1. This method is used when we have a queries for a path from a to b
// 2. Like find the xor of all node in path  from node a to b
// 3. So idea is break the trees into heavy chains and light edges
// 4. Each heavy chains is represented by a segment tree and different heavy chains is connected via light edges
// 5. In a path there is atmost logn heavy chains, So to calculate ans for a path it take logn*logn time
// 6. A path from a-b can be breakdown into logn heavy chains
// 7. we find the anwer for each heavy chain and then merge all the answer 

// implementation
// 1. Creating the tree
// 2. Setting up the subtree size, depth and parent for each node (using a DFS)
// 3. Decomposing the tree into disjoint chains
// 4. Building up the segment tree, here we built diffrent segment for different heavy chains
// 5. Answering queries

#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll pos[200001];
ll size[200001];
ll heavy[200001];
ll height[200001];
ll parent[200001];
ll chainID[200001];
ll values[200001];
vector<ll> adj[200001];
vector<ll> chain[200001];
vector<ll> segment[200001];

void dfs(ll src , ll par , ll ht)
{
    ll mx_sz = 0;
    size[src] = 1;
    height[src] = ht;
    parent[src] = par;
    for(auto &i :adj[src])
    {
        if(i != par)
        {
            dfs(i , src , ht+1);
            size[src] += size[i];
            if(mx_sz < size[i])
            {
                heavy[src] = i;
                mx_sz = size[i];
            }
        }
    }
}

void build_tree(ll id , ll low , ll high , ll segPos)
{
    if(low == high)
    {
        segment[id][segPos] = values[chain[id][low]];
        return;
    }

    ll mid = (low + high)/2;
    build_tree(id, low, mid, 2*segPos+1);
    build_tree(id, mid+1, high, 2*segPos+2);
    segment[id][segPos] = max(segment[id][2*segPos+1] , segment[id][2*segPos+2]);
}

void update(ll id , ll low, ll high , ll segPos , ll idx , ll val)
{
    if(low == high)
    {
        segment[id][segPos] = val;
        return;
    }

    ll mid = (low+high)/2;
    if(idx <= mid) update(id , low , mid , 2*segPos+1 , idx , val);
    else update(id , mid+1 , high , 2*segPos+2 , idx , val);
    segment[id][segPos] = max(segment[id][2*segPos+1] , segment[id][2*segPos+2]);
}

ll query(ll id , ll q_left , ll q_right , ll r_left , ll r_right , ll segPos)
{
    if(q_left <= r_left && q_right >= r_right) return segment[id][segPos];
    if(q_left > r_right || q_right < r_left) return 0;

    ll ans = 0;
    ll mid = (r_left+r_right)/2;
    ans = max(ans , query(id, q_left , q_right , r_left , mid , 2*segPos+1));
    ans = max(ans , query(id, q_left , q_right , mid+1 , r_right , 2*segPos+2));
    return ans;
}

void decompose(ll src)
{
    chain[src].push_back(src);
    for(ll i = 0;i<chain[src].size();i++)
    {
        ll node = chain[src][i];
        chainID[node] = src;
        pos[node] = i;
        for(auto &j: adj[node])
        {
            if(j != parent[node])
            {
                if(j == heavy[node]) chain[src].push_back(j);
                else decompose(j);
            }
        }
    }

    ll sz = chain[src].size();
    segment[src].resize(4*sz , 0);
    build_tree(src , 0 , sz-1 , 0);
}

ll HLDquery(ll a , ll b)
{
    ll ans = 0;
    while(chainID[a] != chainID[b])
    {
        if(height[chainID[a]] > height[chainID[b]]) swap(a , b);
        ans = max(ans , query(chainID[b] , 0 , pos[b] , 0 , chain[chainID[b]].size()-1 , 0));
        b = parent[chainID[b]];
    }

    if(pos[a] > pos[b]) swap(a , b);
    ans = max(ans ,query(chainID[a] , pos[a] , pos[b] , 0 , chain[chainID[b]].size()-1 , 0));
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("zinput.txt", "r", stdin);
    freopen("zoutput.txt", "w", stdout);
#endif

    ll n , q;
    cin >> n >> q;
    for(ll i = 1;i<=n;i++) cin >> values[i];

    for(ll i = 1;i<n;i++) 
    {
        ll x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(1 , -1 , 0);
    decompose(1);

    for(ll i = 1;i<=q;i++)
    {
        ll t , a , b;
        cin >> t >> a >> b;
        if(t == 1) update(chainID[a] , 0 , chain[chainID[a]].size()-1 , 0 , pos[a] , b);
        else cout << HLDquery(a , b) << endl;
    }
}