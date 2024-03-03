#include<bits/stdc++.h>
using namespace std;
// There are many problems that we can solve with the Binary Lifting technique. Just to name a few:

// 1. Finding the Lowest Common Ancestor in a Binary Tree in a logarithmic time. https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/
// 2. Finding minimum and maximum in a logarithmic time.
// 3. Finding the sum of two nodes in a logarithmic time.
// 4. Finding the Kth ancestor of a node in a logarithmic time. 


// 1. Find the nth parent of node in log(n) time
// in binary lift we are make the use of binary number 
// this method we make the auxilary array in which we store the 2^i-th parent of each node if this note exist we put value here acc to ques
// so aux[i][j] :- (2^j)-th parent of node i
// now we use this array to find the kth parent of node n in logn time
// suppose we have to find the 28 parent of 5 then
// 29 = 16 + 8 + 4 + 1
// so we find the 16th parent of 6 says this is x , then we find the 8th parent of x ans so on... 

int find_kth_parent(vector<vector<int>> &aux , int node , int k)
{
    for(int i = 0;i<30;i++)
    {
        if(k&(1<<i)) node = aux[node][i];
        if(node == -1) return -1;
    }
    return node;
}

vector<vector<int>> binary_lift(vector<int> &parent , int n)
{
    vector<vector<int>> aux(n , vector<int>(30 , -1));
    for(int i = 0;i<n;i++) aux[i][0] = parent[i];

    for(int j = 1;j<30;j++)
    {
        for(int i = 0;i<n;i++)
        {
            if(aux[i][j-1] == -1) aux[i][j] = -1;
            else aux[i][j] = aux[aux[i][j-1]][j-1];
        }
    } 
    return aux;
}


// 2. Find the LCA of node a and b in log(n) time 
// to calculate of lca of node we require following additional data structures 
// a. level(n) :where level[i] = level of ith node 
// b. parent(n) :where parent[i] is parent of ith node
// c. aux[i][j] :where aux[i][j] is equal to (2^j)-th parent of i node (calculated by using above method)

ll find_lca(vector<vector<int>> &aux , vector<int> &level , int node1 , int node2)
{
    if(level[node1] > level[node2]) swap(node1, node2);
    node2 = find_kth_parent(node2 , level[node2]-level[node1]);

    if(node1 == node2) return node2;
    
    for(int j = 29;j>=0;j--)
    {
        if(aux[node1][j] == aux[node2][j]) continue;
        node1 = aux[node1][j];
        node2 = aux[node2][j];
    }

    return aux[node1][0];
}

void dfs(vector<vector<int>> &adj , vector<int> &vt , int src , int par , int lvl)
{
    vt[src] = lvl;
    for(auto &i :adj[src])
    {
        if(i != par) dfs(adj , vt , i , src , lvl+1);
    } 
}

void solve(vector<vector<int>> &adj , vector<int> &parent , int node1 , int node2)
{
    ll n = adj.size();
    vector<int> level(n);
    dfs(adj , level , 0 , -1);
    vector<vector<int>> aux = binary_lift(parent , n);

    return find_lca(aux , level , node1 , node2);
    
}

// 3. find the weight of maxiumum edge in path from x to y
void dfs(vector<vector<pair<ll ,ll>>> &adj , vector<vector<ll>> &parent , vector<vector<ll>> &maxEdge , vector<ll> &level , ll src , ll par , ll lvl)
{
    level[src] = lvl;
    parent[src][0] = par;
    for(auto &i :adj[src])
    {
        if(i.first == par) continue;
        maxEdge[i.first][0] = i.second;
        dfs(adj , parent , maxEdge , level , i.first , src , lvl+1);
    }
}

void binary_lifting(vector<vector<ll>> &parent , vector<vector<ll>> &maxEdge , ll n)
{
    for(ll j = 1;j<=20;j++)
    {
        for(ll i = 0;i<n;i++)
        {
            if(parent[i][j-1] != -1) 
            {
                parent[i][j] = parent[parent[i][j-1]][j-1];
                maxEdge[i][j] = max(maxEdge[i][j-1] , maxEdge[parent[i][j-1]][j-1]);
            }
        }
    }
    return;
}

ll find_kth_parent(vector<vector<ll>> &parent , vector<vector<ll>> &maxEdge , ll node , ll k , ll &ans)
{
    for(ll i = 0;i<=20;i++)
    {
        if(k&(1<<i)) 
        {
            ans = max(ans , maxEdge[node][i]);
            node = parent[node][i];
        }
        if(node == -1) return -1;
    }
    return node;
}
ll find_max_edge(vector<vector<ll>> &parent , vector<vector<ll>> &maxEdge , vector<ll> &level , ll a , ll b)
{
    ll ans = 0;
    if(level[a] > level[b]) swap(a , b);
    b = find_kth_parent(parent , maxEdge , b , level[b]-level[a] , ans);

    if(a == b) return ans;
    else
    {
        for(int j = 20;j>=0;j--)
        {
            if(parent[a][j] == parent[b][j]) continue;
            ans = max(ans , max(maxEdge[a][j] , maxEdge[b][j]));
            a = parent[a][j];
            b = parent[b][j];
        }
    }
    ans = max(ans , max(maxEdge[a][0] , maxEdge[b][0]));
    return ans;
}

vector<ll> level(n , 0);
vector<vector<ll>> parent(n , vector<ll>(21 , -1));
vector<vector<ll>> maxEdge(n , vector<ll>(21 , mx));
dfs(adj , parent , maxEdge, level , 0 , -1 , 1);
binary_lifting(parent , maxEdge, n);


// 4. Find kth nearest greater element to left (leetcode)