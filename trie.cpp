#include <bits/stdc++.h>
using namespace std;

struct Trienode
{
    char data;
    int prefix_cnt;
    Trienode* child[26];

    public:
    Trienode(char val)
    {
        data = val;
        prefix_cnt = 0;
        for(int i = 0; i < 26;i++) 
        {
            child[i] = NULL;
        }
    }
};

Trienode *root = new Trienode('.'); // root node of trie
void insert(string str)
{
    Trienode *curr = root;
    int idx, len = str.length();
    for(int i = 0; i < len; i++)
    {
        idx = str[i] - 'a';
        if(curr->child[idx] == NULL) // make the new node 
        {
            Trienode *node = new Trienode(str[i]);
            curr->child[idx] = node;
        }
        curr = curr->child[idx];
        curr->prefix_cnt += 1; // increment prefix count
    }
}


int countPrefix(string str)
{
    Trienode *curr = root;
    int idx , len = str.length();
    for (int i = 0; i < len; i++)
    {
        idx = str[i] - 'a';
        if(curr->child[idx] == NULL)
            return 0; //No string with given prefix is present
        curr = curr->child[idx];
    }
    return curr->prefix_cnt;
}

int main()
{
    string a = "army";
    string b = "arm";
    string c = "arms";
    string d = "ary";
    string e = "amy";
    string f = "api";

    // insert words in trie
    insert(a);
    insert(b);
    insert(c);
    insert(d);
    insert(e);
    insert(f);

    cout << "No of strings with given prefix " << countPrefix("a") << endl;
    cout << "No of strings with given prefix " << countPrefix("ar") << endl;
    cout << "No of strings with given prefix " << countPrefix("arm") << endl;
    cout << "No of strings with given prefix " << countPrefix("army") << endl;
    cout << "No of strings with given prefix " << countPrefix("armi") << endl;
    cout << "No of strings with given prefix " << countPrefix("api") << endl;
    // cout<<"Deletion...STARTED\n";
    // Triedelete(a);
    // Triedelete(d);
    cout<<"DONE...\n\n";


    return 0;
}