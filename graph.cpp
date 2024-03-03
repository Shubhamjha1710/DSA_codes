#include <bits/stdc++.h>
using namespace std;
#define ll long long
// algorithm 

// dfs
// 1) tc-> O(E+V) , sc-> O(V);
void dfs(vector<vector<ll>> &adj , ll source)
{
    if(visited[source] == true) return;
    cout << source << " ";
    visited[source] = true;
    for(auto &i : adj[source])
    {
        if(visited[i] == false) dfs(adj, i);
    }
}

//  ***********************************************************************************************************************************

// bfs
// 1) tc-> O(E+V) , sc-> O(V);
// 2) this will considered as level order tarversals
// 3) when graph is unweighted bfs can be used to find the shortest distance
void bfs(vector<vector<ll>> &adj, ll src, ll n)
{
    queue<ll> q;
    bool visited[n + 1] = {false};
    visited[src] = true;
    q.push(src);

    while (q.empty() == false)
    {
        ll p = q.front();
        q.pop();
        for (auto &i : adj[p])
        {
            if (visited[i] == false)
            {
                q.push(i);
                cout << i << " ";
                visited[i] = true;
            }
        }
    }
}


//  0-1 bfs
// 1) used when there is only two types of weights present in graph i.e 0 or 1
// 2) now in normal bfs at single time there is only nodes of two different levels is present
// 3) so edges with weights 0 is treated at same level , so immediate consideration (pushed from the front)
// 4) edges with weight 1 is considered as one level below , so can be considered later( pushed from back)
// 5) that why use deque instead of normal queue

// this will calculate the shortest path from 1 to n
int bfs0_1(vector<vector<vector<int>>> &vt , int n)
{
    vector<int> dist(n+1 , INT_MAX);
    deque<int> q;
    q.push(1);
    dist[1] = 0
    while(q.empty() == false)
    {
        int src = q.front();
        q.pop_front();

        for(auto &i :adj[src])
        {
            int curr = i[0] , weight = i[1];
            if(dist[src] + weight < dist[curr])
            {
                dist[curr] = dist[src] + weight;
                if(weight == 1) q.push_back(curr);
                else q.push_front(curr);
            }
        }
    }

    return dist[n];
}

// multi source bfs


// **********************************************************************************************************************

// Shortest distance alogithms

// DIJKSTRA ALGORITHM  (shortest distance of each vertex from source vertex)
// 1) tc-> O(ElogV) sc-> O(V)

// use of pq in dijkstra is helpful to reduce time only when you also use visit array
void dijkstra(vector<vector<vector<ll>>> &adj , vector<ll> src , vector<ll> &visit , vector<ll> &dist) 
{
    dist[src] = 0;
    priority_queue<vector<ll> , vector<vector<ll>> , greater<vector<ll>>> pq;
    pq.push({0 , src});

    while(pq.empty() == false)
    {
        ll curr = pq.top()[1];
        ll cost = pq.top()[0];
        pq.pop();

        if(visit[curr] == 1) continue;

        visit[curr] = 1;
        for(auto &i :adj[curr])
        {
            ll next = i[0] , next_dist = i[1];
            if(cost + next_dist < dist[next])
            {
                dist[next] = cost + next_dist;
                pq.push({dist[next] , next});
            }
        }
    }
}

// BELLMAN-FORD ALGORITHM (also for negative weights graphs)
// 1) at ith iteration we calculate the shortest distance between vertex with i edges 
// 2) doesn't not work in case of undirected graph as single edges may treated as cycle
// 2) tc-> O(V*E) , sc->(V*V)
// for eg.
// https://leetcode.com/problems/cheapest-flights-within-k-stops/description/ 
void bellman_ford(vector<vector<ll>> &edges , ll V , ll E int src)
{
    vector<ll> dist(V , INT_MAX);
    dist[src] = 0;

    for(ll j = 0;j<V-1;j++)
    {
        for(ll i = 0;i<E;i++)
        {
            if(dist[edges[i][0]] != INT_MAX && dist[edges[i][1]] > dist[edges[i][0]] + edges[i][2])
            {
                dist[edges[i][1]] = dist[edges[i][0] + edges[i][2];
            }
        }
    } 

    // check for negative-weight cycles.
    for(ll i = 0;i<E;i++) 
    {
        if(dist[edges[i][0]] != INT_MAX && dist[edges[i][1]] > dist[edges[i][0]] + edges[i][2])
        {
            cout << "Negative weight cycle";
        }
    }
    cout << "NO";
}

// FLYOD WARSHALL ALGORITHM (shortest distance between each pair of vertex)
// 1) tc-> O(V*V*V)  sc-> O(V*V)

void flyod_warshall(vector<vector<ll>> &dist , ll v)
{
    // initailly dist[i][j] == Inf (if there is not the edge between i to j)
    // dist[i][j] = cost (if there is the edge between i to j)
    for(ll k = 0;i<v;k++)
    {
        for(ll i =0;i<v;i++)
        {
            for(ll j =0;j<v;j++)
            {
                if(dist[i][k]!= INT_MAX && dist[j][k] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // to check wheater there is negative weight cycle we check if dist[v][v] < 0
    for(ll i = 0;i<v;i++)
    {
        if(dist[v][v] < 0) // yes negative cycle
    }
}


// *************************************************************************************************************************

// Minimum spanning tree algorithms
// 1) connected graph with no cycles 
// 2) n-1 edges present in the graph

// KRUSKAL ALGORITHM 
// 1) Sort each edges according to there weight 
// 2) Pick the minimum weighted edge
// 3) Check wheather it addition form the cycle or not (using union find algo)
// 4) Repeat the same procedure for N-1 edges
// tc -> ElogE , sc-> O(V+E)
int find(vector<int> &dsu , int a)
{
    if(dsu[a] == a) return a;
    return dsu[a] = find(dsu, dsu[a]);
}

void unions(vector<int> &dsu , int a , int b)
{
    a = find(dsu, a);
    b = find(dsu, b);
    dsu[b] = a;
}

void kruskal(vector<vector<int>> &edges )
{
    int n = edges.size();
    priority_queue<vector<int> , vector<vector<int>> , greater<vector<int>>> pq;
    for(int i = 0;i<n-1;i++)
    {
        pq.push({edges[i][2] , edges[i][0] , edges[i][1]})
    }

    vector<int> dsu(n , 0);
    vector<vector<int>> mst;
    for(int i = 0;i<n;i++) dsu[i] = i;

    while(pq.empty() == false)
    {
        int a = pq.top()[1] , b = pq.top()[2] , cost = pq.top()[0];
        pq.pop();
        if(find(dsu , a) != find(dsu , b))
        {
            mst.push_back({a , b , cost});
            unions(dsu , a, b);
        }
    }
}

// PRIMS ALGORITHM
// 1) make the mst set which include the node which is currently present in mst
// 2) now take the edge with minimum weight edge and with that which is not present in mst set
// 3) now add this node to mst set and add this edge in spanning tree
// 4) repeat the following procedure until we find n-1 edges
// tc -> O(ElogV) , sc-> O(E+V)
void Prims(vector<vector<vector<int>>> &adj , ll n);
{
    int mst_weight = 0;
    vector<int> parent(n , -1);
    vector<int> visit(n , 0);
    priority_queue<vector<int> , vector<vector<int>> , greater<vector<int>>>pq;

    pq.push({0 , 0 , -1});
    while(pq.empty() == false)
    {
        int cost = pq.top()[0];
        int src = pq.top()[1];
        int par = pq.top()[2];
        pq.pop();
        
        if(visit[src] == 1) continue;
        
        visit[src] = 1;
        parent[src] = par;
        mst_weight += cost;
        for(auto &i :adj[src])
        {
            int next = i[0] , cost = i[1];
            if(visit[next] == 0)
            {
                pq.push({cost , next , src});
            }
        }
    }
    // to get the mst do dfs from node 0
}

// Reverse Delete algorithm for MST
// 1)Sort the edges on decreasing order of weights
// 2)Now check if after rempval of this edges make graph disconnected or not
// 3) If after removal graph becomes disconnected then don't remove it else remove the edge

void dfs(vector<vector<int>> &adj , vector<bool> &visit , int src)
{
    visit[src] = true;
    for(auto &i :adj[src])
    {
        if(visit[i] == false) dfs(adj , visit , i);
    }
}

bool is_connected(vector<vector<int>> &adj , int V , int E)
{
    vector<bool> visit(V+1 , 0);
    dfs(adj , visit , 0);
    for(int i = 0;i<V;i++)
    {
        if(visit[i] == false) return false;
    }
    return true;
}
int RevDelMST(vector<vector<int>> &adj , vector<vector<int>> &edges, int V, int E) 
{
    int ans = 0;
    sort(edges.begin() , edges.end() , greater<vector<int>>());
    for(auto &i: edges)
    {
        int cost = i[0];
        int a = i[1] , b = i[2];
        adj[a].erase(find(adj[a].begin() , adj[a].end() , b));
        adj[b].erase(find(adj[b].begin() , adj[b].end() , a));
        if(is_connected(adj , V , E) == false)
        {
            ans += cost;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }
    
    return ans;
}

// ***********************************************************************************************************************

// TOPOLOGICAL SORTING
// always start with that vertes whoose in degree is zero
// Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices 
// such that for every directed edge u v, vertex u comes before v in the ordering.
// tc -> O(V+E) , sc-> O(V)

void topo_sort_com(vector<int> &ans , vector<vector<int>> &adj , int src , vector<bool> &visit)
{
    visit[src] = 1;
    for(auto &i :adj[src])
    {
        if(visit[i] == 0)
            topo_sort_com(ans , adj , i , visit);
    }

    ans.push_back(src);
}   

vector<int> topoSort(vector<vector<int>> &adj)
{
    vector<int> ans;
    int n = adj.size();
    vector<int> visit(n , 0);   


    for(int i = 0;i<n;i++)
    {
        if(visit[i] == 0)
        {
            topo_sort_com(st , adj , i , ans);
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

// KHAN ALGORITHM
vector<int> topoSort(int V, vector<vector<int>> adj) 
{
    queue<int> q;
    vector<int> ans;
    vector<int> indeg(V , 0);
    for(int i = 0;i<V;i++)
    {
        for(auto &j :adj[i]) indeg[j]+=1;
    }
    for(int i = 0;i<V;i++)
    {
        if(indeg[i] == 0) q.push(i);
    }
    
    while(q.empty() == false) 
    {
        int src = q.front(); q.pop();
        ans.push_back(src);
        for(auto &i :adj[src])
        {
            indeg[i]-=1;
            if(indeg[i] == 0) q.push(i);
        }
    }
    
    return ans;
}

// BRIDGES IN GRAPH
// https://codeforces.com/blog/entry/71146
// 1) The basic concept is if the lowest discovery time for a child node is greater than the discovery of current node this means there is no back edges hence the edges between node and child node act as bridges.
// 2) And if there is back edges then update the lowest discovery time for that child node
// TC -> O(V+E) SC-> O(V+E)
vector<int> discovery;
vector<bool> visited;
vector<int> lowest_dis_time;
void dfs(vector<vector<int>> &adj , vector<vector<int>> &ans , int src , int parent , int &time)
{
    visited[src] = true;
    discovery[src] = time;
    lowest_dis_time[src] = time;
    time+=1;
    
    for(auto &child :adj[src])
    {
        if(visited[child] == false)
        {
            dfs(adj , ans , child , src , time);
            lowest_dis_time[src] = min(lowest_dis_time[child] , lowest_dis_time[src]);
            
            // check for bridge
            if(discovery[src] < lowest_dis_time[child])
                ans.push_back({src , child});
        }
        else 
        {
            if(child != parent)
            {
                lowest_dis_time[src] = min(discovery[child] , lowest_dis_time[src]);
            }
        }
    }
}

vector<vector<int>> findBridges(int n, vector<vector<int>>& connections) 
{
    int sz = connections.size();
    vector<vector<int>> adj(n , vector<int>());
    for(int i = 0;i<sz;i++)
    {
        adj[connections[i][0]].push_back(connections[i][1]);
        adj[connections[i][1]].push_back(connections[i][0]);
    }
    
    discovery.resize(n , -1);
    visited.resize(n , false);
    lowest_dis_time.resize(n , INT_MAX);
    
    vector<vector<int>> ans;
    for(int i = 0;i<n;i++)
    {
        if(visited[i] == false)
        {
            int time = 0;
            dfs(adj , ans , i , -1 , time);
        }
    }
    
    return ans;
}

// ARTICULATION POINT IN GRAPH
// 1) If the node is root node and it has more than 2 child the it will always act as articulation point 
// 2) if the node is non root node the we have to check for back edges , similar concept as to find bridges 
// tc -> O(V+E) , sc-> O(V+E);
int times = 0;
void dfs(vector<vector<int>> &adj , vector<int> &visit , vector<int> &discovery , vector<int> &lowest_discovery , vector<int> &ans , int src , int parent)
{
    visit[src] = 1;
    discovery[src] = times;
    lowest_discovery[src] = times;
    times+=1;
    
    bool flag = false; // to check if we already pushed it in ans
    int cnt = 0;
    for(auto &child :adj[src])
    {
        if(visit[child] == 0)
        {
            cnt+=1;
            dfs(adj , visit , discovery , lowest_discovery , ans , child , src);
            lowest_discovery[src] = min(lowest_discovery[child] , lowest_discovery[src]);
            
            // check for articulation point
            if(discovery[src] <= lowest_discovery[child] && parent != -1 && flag == false)
            {
                flag = true;
                ans.push_back(src);
            }
        }
        else 
        {
            if(child != parent)
            {
                lowest_discovery[src] = min(discovery[child] , lowest_discovery[src]);
            }
        }
    }
    
    if(parent == -1 && cnt >= 2 && flag == false) ans.push_back(src);
}
vector<int> articulationPoints(int V, vector<vector<int>>adj) 
{
    vector<int> ans;
    vector<int> visit(V , 0);
    vector<int> discovery(V , -1);
    vector<int> lowest_discovery(V , INT_MAX);
    
    for(int i = 0;i<V;i++)
    {
        if(visit[i] == 0)
        {
            dfs(adj , visit , discovery , lowest_discovery , ans , i , -1);
        }
    }
    sort(ans.begin() ,ans.end());
    if (ans.size() == 0)  return {-1};
    return ans;
    // Code here
}


// KOSARAJU'S ALGORITHM  || STRONGLY CONNECTED COMPONENTS (SCC)
// for algo read complete page https://www.geeksforgeeks.org/strongly-connected-components/
// https://practice.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1 (read editorial)
// tc -> O(V+E) , sc -> O(V+E)

void topoDFS(vector<vector<int>> &adj , stack<int> &st , vector<int> &visit , int src)
{
    visit[src] = 1;
    for(auto &i :adj[src])
    {
        if(visit[i] == 0)
        {
            topoDFS(adj , st , visit , i);
        }
    }
    st.push(src);
}

void dfs(vector<vector<int>>&adj , vector<int>&comp , vector<int> &visit , int src)
{
    visit[src] = 1;
    comp.push_back(src);
    for(auto &i :adj[src])
    {
        if(visit[i] == 0) dfs(adj , comp ,visit , i);
    }
}

vector<vector<int>> findSCC(vector<vector<int>> &transpose , stack<int> &st , int V)
{
    vector<int> visit(V , 0);
    vector<vector<int>> ans;
    while(st.empty() == false)
    {
        if(visit[st.top()]) st.pop();
        else 
        {
            vector<int> comp
            dfs(transpose , comp , visit , st.top());
            ans.push_back(comp);
        }
    }
    return ans;
}

vector<vector<int>> kosaraju(int V, vector<vector<int>> adj)
{
    stack<int> st;
    vector<int> visit(V , 0);
    for(int i = 0;i<V;i++)
    {
        if(visit[i] == 0) topoDFS(adj , st , visit , i);
    }
    
    vector<vector<int>> transpose(V+1);
    for(int i = 0;i<V;i++)
    {
        for(auto &j :adj[i]) 
            transpose[j].push_back(i);
    }
    
    return findSCC(transpose , st , V);
}


// Euler Graph (if it possible to draw a given graph without lifting pencil from the paper and without tracing any of the edges more than once then this graph is eulerian)
// 1. Walk : Any random tarversal is in graph is called as walk
// 2. Trail :A walk in which no edge is repeated is called as trail
// 3.Euler path (semi eulerian graph) is walk is that visit each edge exactly once and euler circuit is euler path which start and end at same vertex.
// 4. A Graph is said to be eulerian if it has eulerian cycle 
// So euler Path is superset of euler circuit 

// Condition for euler circuit
// a. start and end should be same 
// b. every edge must be visited only once(all present in single component)

// Condition for Euler Graph
// 1.Start Node = End Node (traversal)
// 2.Every edge must visited only once 
// 3.All vertices have even degree one for coming at this vertex and one for going out that vertex
// 4.All vertices with non-zero degree are connected. We don’t care about vertices with zero degree because they don’t belong to Eulerian Cycle or Path (we only consider all edges). 

// Algo for Euler graph
// 1. Connectivity check:- means all non zero degree vertex belong to single component (use dfs)
// 2. Count old degree Node
// count = 0 (euler graph)
// count = 2 (semi euler graph)
// count > 2(not euler graph)


// Hierholzer’s algorithm (for directed graphs)
// Starting point of euler graph is node with outdegree - indegree = 1
// This algorithm is used to find the euler path in the directed graph in O(E) time 
// https://www.youtube.com/watch?v=8MpoO2zA2l4
vector<int> Hierholzer(vector<vector<int>> &adj , int src)
{
    stack<int> st;
    vector<int> ans;
    st.push(src);

    while(st.empty() == false)
    {
        int src = st.top();
        if(adj[src].size())
        {
            st.push(adj[src].back());
            adj[src].pop_back();
        }
        else
        {
            ans.push_back(src);
            st.pop();
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}



// Dynamic Connectivity:- when there is m edges in graph and u have to find the number of connected compo after each query 
// there may be 3 case acc to type of query
// 1. when all query are type of adding the edges (incremental connectivity normally done by dsu)
// 2. when all query are type of removing the edges (decremental connectivity normally done by dsu , but traverse query in reverse order , and add edges in reverse order of query)
// 3. when query may be of any type (incremental connectivity + decremental connectivity = dynamic connectivity)


// comman questions
// https://www.geeksforgeeks.org/maximum-height-of-tree-when-any-node-can-be-considered-as-root/



// Bipartite Graph
void isBipartite(vector<vector<ll>> &adj , vector<ll> &visit , ll col , ll src , bool &flag)
{
    visit[src] = col;
    for(auto &i :adj[src])
    {
        if(visit[i] == -1) isBipartite(adj , visit , (1^col) , i , flag);
        else if(visit[i] == col) flag = false;
    }
}

// Maximum Bipartite Matching
// A matching in a Bipartite Graph is a set of the edges chosen in such a way that no two edges share an endpoint. Maximum Bipartite matching is such matching in which we have maximum number of edges.
// This Maximum bipartite matching is useful in many real life problems such as "There are M job applicants and N jobs. Each applicant has a subset of jobs that he/she is interested in. Each job opening can only accept one applicant and a job applicant can be appointed for only one job. Find an assignment of jobs to applicants in such that as many applicants as possible get jobs."
https://www.geeksforgeeks.org/maximum-bipartite-matching/
// we will use the ford fulkerson method to find the maximum matching pair
// the edge from applicants, i to job, j has a capacity of 1 and we append to new node souce and sink has to find the maximum flow from sink node
//             0/1                    0/1                 0/1
// source ----------> applicants   ------------>  jobs ----------> sink
// here capacity of 1 between source and applicant ensures that each person gets 1 one jab if a person can get x jabs then capacity corresponding to that person is 0/x
// here capacity of between jobs and sink is 0/1 means single position for thid job, if there is multiple position for this job then change it to 0/x.

// In bipartite matching 
// In bpm(), we one by one try all jobs that an applicant ‘u’ is interested in until we find a job, or all jobs are tried without luck. For every job we try, we do following. 
// If a job is not assigned to anybody, we simply assign it to the applicant and return true. If a job is assigned to somebody else say x, then we recursively check whether x can be assigned some other job. To make sure that x doesn’t get the same job again, we mark the job ‘v’ as seen before we make recursive call for x. If x can get other job, we change the applicant for job ‘v’ and return true. We use an array maxR[0..N-1] that stores the applicants assigned to different jobs.
// If bmp() returns true, then it means that there is an augmenting path in flow network and 1 unit of flow is added to the result in maxBPM(). 