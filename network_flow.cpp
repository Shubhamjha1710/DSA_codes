// FORD FULKERSON ALGORITHM
// ford fulkerson algorithm is widely used algorithm to solve the maximum flow problem in flow network. the maximum flow problem involves determing the maximum amount of flow that can be sent from source to sink vertex in direted weighted graph with constraints on edges

// each edges have following constraints 
// 1. flow on edges doesnt exceed the given capacity of the edges
// 2. incoming flow is equal to the outgoing flow

// The algorithm works by iteratively finding an augmenting path, which is a path from the source to the sink in the residual graph, i.e., the graph obtained by subtracting the current flow from the capacity of each edge. The algorithm then increases the flow along this path by the maximum possible amount, which is the minimum capacity of the edges along the path.

// Residual Graph of a flow network is a graph which indicates additional possible flow. If there is a path from source to sink in residual graph, then it is possible to add flow. Every edge of a residual graph has a value called residual capacity which is equal to original capacity of the edge minus current flow. 
// Residual capacity is basically the current capacity of the edge. Residual capacity is 0 if there is no edge between two vertices of residual graph. We can initialize the residual graph as original graph as there is no initial flow and initially residual capacity is equal to original capacity. We find the augment path iteratively untill we have a residual path
#include<bits/stdc++.h>
using namespace std;
#define ll long long
bool bfs(vector<vector<ll>> &residual , ll start , ll end , vector<ll> &parent , ll n)
{
    queue<ll> q;
    vector<ll> visit(n , 0);
    q.push(start); visit[start] = 1;
    parent[start] = -1;

    while(q.empty() == false)
    {
        ll src = q.front(); q.pop();
        for(ll i = 0;i<n;i++)
        {
            if(visit[i] == 0 && residual[src][i] > 0)
            {
                if(i == end)
                {
                    parent[i] = src;
                    return true;
                }

                q.push(i);
                visit[i] = 1;
                parent[i] = src;
            }
        }
    }
    return false;
}

ll ford_fulkerson(vector<vector<pair<ll ,ll>>> &adj , ll start , ll end , ll n)
{
    vector<vector<ll>> residual(n , vector<ll>(n));
    for(ll i = 0;i<n;i++)
    {
        for(auto &j :adj[i]) residual[i][j.first] = j.second; 
    }

    ll max_flow = 0;
    vector<ll> parent(n , -1);
    while(bfs(residual , start , end , parent , n))
    {
        ll path_flow = INT_MAX;
        for(ll v = end; v != start; v = parent[v])
        {
            ll u = parent[v];
            path_flow = min(path_flow, residual[u][v]);
        }
        for(ll v = end; v != start; v = parent[v])
        {
            ll u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main()
{
    ll n = 6;
    vector<vector<pair<ll ,ll>>> adj(n , vector<pair<ll ,ll>>());
    adj[0].push_back({1, 16});
    adj[0].push_back({2, 13});
    adj[1].push_back({2, 10});
    adj[1].push_back({3, 12});
    adj[2].push_back({1, 4});
    adj[2].push_back({4, 14});
    adj[3].push_back({2, 9});
    adj[3].push_back({5, 20});
    adj[4].push_back({3, 7});
    adj[4].push_back({5, 4});
    cout << ford_fulkerson(adj , 0 , 5 , n) << endl;
}



