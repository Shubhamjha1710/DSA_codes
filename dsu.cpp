// Disjoint Set Union
// this will use ackermann fucntion

#include<bits/stdc++.h>
using namespace std;

// Basis DSU class
template <typename T> class DSU {
    public: 
    vector<T> dsu;
    vector<T> rank;

    DSU(T sz) {
        this->dsu = vector<T> (sz);
        this->rank = vector<T> (sz);
        for(T i = 0;i<sz;i++) {
            this->dsu[i] = i;
            this->rank[i] = i;
        }
    }

    T find(T a) {
        if((this->dsu[a]) == a) {
            return a;
        } else {
            return this->dsu[a] = find(this->dsu[a]);
        }
    }

    void unions(T a, T b) {
        a = this->find(a);
        b = this->find(b);

        if(a != b) {
            if(this->rank[a] < this->rank[b]) {
                swap(a , b);
            } 

            this->dsu[b] = a;
            this->rank[a] += (this->rank[b]);
        }
    }
};

// Dsu Rollbacks 
// Rollbacks in Dsu is complex when you are using path compression with dsu because of large change occurs in dsu it is in effecient to store all that changes
// So only use rank compression, dont use the path compression then time complexity of union find is logn which is pretty good so store all merging history inside a stack and pop back current top of stack and rollback to previous version 
// store <leader , previous parent , rank of leader> in stack
// and make dsu[leader] = previous parent and rank[leader] = rank of leader and pop stack top, in most cases leader = previous parent 

template <typename T> class Rollback_DSU {
    public: 
    vector<T> dsu;
    vector<T> rank;
    stack<pair<T, T>> st;

    Rollback_DSU(T sz) {
        this->dsu = vector<T> (sz);
        this->rank = vector<T> (sz);
        for(T i = 0;i<sz;i++) {
            this->dsu[i] = i;
            this->rank[i] = i;
        }
    }
    
    T find(ll a)
    {
        if((this->dsu[a]) == a) return a;
        return find(dsu, dsu[a]); // no path compression
    }

    void unions(T a, T b) {
        a = find(dsu, a);
        b = find(dsu, b);
        
        if(a != b) {
            if(rank[a] < rank[b]) {
                swap(a, b);
            }

            st.push({b , rank[b]});
            dsu[b] = a;
            rank[a] += rank[b];
        }
    }

    void rollback()
    {
        T initial = st.top().first;
        T initial_rank = st.top().second;
        rank[find(initial)]-=rank[initial];

        st.pop();
        dsu[initial] = initial;
        rank[initial] = initial_rank;
    }
};
