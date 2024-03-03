https://www.geeksforgeeks.org/matrix-exponentiation/ 
// nth fibonacci number
#include<bits/stdc++.h>
using namespace std;
long long M = 1e9+7;
// yee pattern badalta rehta hai ki konsa se pe ans aaega , acc to unit matrix
vector<vector<long long>> multiply(vector<vector<long long>> &a , vector<vector<long long>> &b)
{
    vector<vector<long long>>ans (2 , vector<long long>(2));
    ans[0][0] = ((a[0][0]*b[0][0])%M + (a[0][1]*b[1][0])%M)%M;
    ans[0][1] = ((a[0][0]*b[0][1])%M + (a[0][1]*b[1][1])%M)%M;
    ans[1][0] = ((a[1][0]*b[0][0])%M + (a[1][1]*b[1][0])%M)%M;
    ans[1][1] = ((a[1][0]*b[0][1])%M + (a[1][1]*b[1][1])%M)%M;
    return ans;
}

vector<vector<long long>> power(vector<vector<long long>> aux , int n)
{
    vector<vector<long long>> res  = {{1,0},{0,1}};
    while(n)
    {
        if(n%2 == 0)
        {
            aux = multiply(aux , aux);
            n/=2;
        }
        else
        {
            res = multiply(aux , res);
            n-=1;
        }
    }
    return res;
}
int nthFibonacci(int n)
{
    vector<vector<long long>> aux = {{1,1},{1,0}};
    vector<vector<long long>> n_th = power(aux , n-1);
    return n_th[0][0];
    // code here
}

// Application
// 1. Given n points ,apply m transformations to each of these points. Each transformation can be a shift, a scaling or a rotation around a given axis by a given angle. 
// this can be done in O(nlogK) time using matrix exponentiation (https://cp-algorithms.com/algebra/binary-exp.html#fast-application-of-a-set-of-geometric-operations-to-a-set-of-points)

// 2.Given a directed unweighted graph of n vertex find the number of path of length k from any vertex u to any other vertex v.
// The algorithm consists of raising the adjacency matrix M of the graph (a matrix where adj[i][j] = 1 if there is an edge from i to j,or 0 otherwise) to the k-th power. Now adj[i][j] will be the number of paths of length k from i to j. The time complexity of this solution is O(n^3*log k).
// derivation of this concept
// https://codeforces.com/contest/222/problem/E

// 3.  You are given a sequence of length n. Apply to it a given permutation k times.
// question for better understanding https://www.codechef.com/problems/RIFFLES



// Practice Contest :- https://codeforces.com/gym/102644