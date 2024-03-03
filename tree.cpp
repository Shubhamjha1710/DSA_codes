#include <bits/stdc++.h>
using namespace std;

struct node {
    node *left;
    node *right;
    int data;
    node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

node* create_tree(vector<int> &vt)
{
    // here we taking the input from the vector
    int val;
    int k = 0 , n = vt.size();
    queue<node*> q;
    // cout << "Enter the value of root node" << endl;
    // cin >> val; 
    if(k >= n) val = -1;
    else 
    {
        val = vt[k];
        k+=1;
    }

    node *root = new node(val);
    q.push(root);

    while(q.empty() == false) 
    {
        node *tp = q.front();
        q.pop();

        // cout << "Enter the value of left child of "<<tp->data << endl;
        // cin >> val;
        if(k >= n) 
            val = -1;
        else 
        {
            val = vt[k];
            k+=1;
        }

        if(val != -1)
        {
            node *p = new node(val);
            tp->left = p;
            q.push(p);
        }

        // cout << "Enter the value of right child " <<tp->data << endl;
        // cin >> val;
        if(k >= n) 
            val = -1;
        else 
        {
            val = vt[k];
            k+=1;
        }
        if(val != -1)
        {
            node *p = new node(val);
            tp->right = p;
            q.push(p);
        }
    }
    return root;
}
void display_in(node *root)
{
    if(root == NULL) return;
    display_in(root->left);
    cout << root->data << " ";
    display_in(root->right);
}
void display_pre(node *root)
{
    if(root == NULL) return;
    cout << root->data << " ";
    display_pre(root->left);
    display_pre(root->right);
}
void display_post(node *root)
{
    if(root == NULL) return;
    display_post(root->left);
    display_post(root->right);
    cout << root->data << " ";
}
void preorder(node *root)
{
    stack<node*> st;
    node *t = root;
    while(st.empty() == false || t != NULL)
    {
        if(t != NULL)
        {
            cout << t->data << " ";
            st.push(t);
            t = t->left;
        }
        else 
        {
            t  = st.top();
            st.pop(); 
            t = t->right;
        }
    }
}
void inorder(node* root)
{
    stack<node*> st;
    node* t = root;
    while(st.empty() == false || t != NULL)
    {
        if(t == NULL)
        {
            t = st.top();
            st.pop();
            cout << t->data << " ";
            t = t->right;
        }
        else
        {
            st.push(t);
            t = t->left;
        }
    }
}
void postorder(node* root)
{
    stack<pair<node*,int>> st;
    pair<node*,int> temp;
    node* t = root;
    while (st.empty() == false || t != NULL)
    {
        if(t != NULL)
        {
            st.push({t,1});
            t = t->left;
        }
        else 
        {
            temp = st.top();
            st.pop();
            if(temp.second > 0)
            {
                temp.second = -1;
                st.push(temp);
                t = (temp.first)->right;
            }
            else 
            {
                cout << (temp.first)->data << " ";
                t = NULL;
            }
        }
    }
}
void levelorder(node *root)
{
    queue<node*>q;
    node* t;
    q.push(root);
    while(q.empty() == false)
    {
        t = q.front();
        q.pop();
        cout << t->data << " ";
        if(t->left != NULL)
        {
            q.push(t->left);
        }
        if(t->right != NULL)
        {
            q.push(t->right);
        }
    }
}

void morris_preorder(node *root)
{
    node *curr = root;
    while(curr != NULL)
    {
        if(curr->left == NULL)
        {
            cout << curr->data << " ";
            curr = curr->right;
        }
        else 
        {
            node *prev = curr->left;
            while(prev->right && prev->right != curr) prev = prev->right;

            if(prev->right == NULL)
            {
                prev->right = curr;
                cout << curr->data << " ";
                curr = curr->left;
            }
            else
            {
                prev->right = NULL;
                curr = curr->right;
            }
        }
    }
}
void morris_inorder(node *root)
{
    node *curr = root;
    while(curr != NULL)
    {
        if(curr->left == NULL)
        {
            cout << curr->data << " ";
            curr = curr->right;
        }
        else 
        {
            node *prev = curr->left;
            while(prev->right && prev->right != curr) prev = prev->right;

            if(prev->right == NULL)
            {
                prev->right = curr;
                curr = curr->left;
            }
            else
            {
                prev->right = NULL;
                cout << curr->data << " ";
                curr = curr->right;
            }
        }
    }
}


int main()
{
    // Shubham Kumar Jha
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

// #ifndef ONLINE_JUDGE
//     freopen("zinput.txt", "r", stdin);
//     freopen("zoutput.txt", "w", stdout);
// #endif
    // int num;
    // cin >> num;
    vector<int> vt = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    node* root = create_tree(vt);
    cout << "Recursive Preorder ";display_pre(root);cout << endl;
    cout << "Iterative Preorder ";preorder(root); cout << endl;
    cout << "Morris Preorder ";morris_preorder(root); cout << endl;
    cout << "Recursive Inorder ";display_in(root);cout << endl;
    cout << "Iterative Inorder ";inorder(root);cout << endl;
    cout << "Morris Inorder ";morris_inorder(root); cout << endl;
    cout << "Recursive Postorder ";display_post(root);cout << endl;
    cout << "Iterative Postorder ";postorder(root);cout << endl;
    cout << "Iterative LevelOrder ";levelorder(root);cout << endl;

    return 0;
}