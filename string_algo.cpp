#include<bits/stdc++.h>
using namespace std;
#define M 998244353
#define endl "\n"
#define ll long long
#define lld long double

// String algorithms
// Manacher Algorthm
ll manacher(string &s , ll n)
{
    // build hashed string
    string str = "#";
    for(ll i = 0; i < n; i++) 
    {
        str.push_back(s[i]);
        str.push_back('#');
    }

    n = str.length();
    ll l = 1 , r = 1;
    vector<ll> pallin_len(n ,1);
    for(ll i = 1;i<n;i++)
    {
        if(l + r - i >= 0) pallin_len[i] = max(0 , min(r-i , pallin_len[l + (r-i)]))
        while(i - pallin_len[i] >= 0 && i + pallin_len[i] < n && s[i+pallin_len[i]] == s[i-pallin_len[i]]) 
        {
            pallin_len[i]+=1;
        }

        if(i + pallin_len[i] > r)
        {
            l = i-pallin_len[i];
            r = i+pallin_len[i];
        }   
    }
}

// Z algorithm(Z function)
// The Z-function a string is an array of length n where the ith element is equal to the greatest number of characters starting from the position i that coincide with the first characters of s.
// so z[i] = longest comman prefix for suffix str[i..n]
// similar to manacher algorithm , use of segement and box;
// eg string : xyzxyz
// here box [l...r] show this substring is prefix of string str of length (r-l+1)
vector<ll> zAlgorithm(string &str , ll n)
{
    vector<ll> vt(n , 0);
    ll l = 0 , r = 0;
    for(ll i = 1;i<n;i++)
    {
        if(l <= i) vt[i] = max(0LL , min(r - i , vt[i-l]));
        while(i+vt[i] < n && str[vt[i]] == str[i+vt[i]]) vt[i]+=1;

        if(r < i+vt[i])
        {
            l = i;
            r = i+vt[i];
        }
    }
    return vt;
}


// Lps/prefix function :- The prefix function for a string is defined as an array vt of length n, where vt[i] is the length of the longest proper prefix of the substring s[0...i]which is also a suffix of this substring. A proper prefix of a string is a prefix that is not equal to the string itself. By definition, vt[0] = 0.  
// https://youtu.be/jXUP-sAzXRQ?t=383
vector<ll> lps_generate(string &str)
{
    ll n = str.length();
    vector<ll> lps(n);
    lps[0] = 0;
    for(ll i = 1; i < n; i++)
    {
        ll len = lps[i-1];
        while(len > 0 && str[len] != str[i])
            len = lps[len-1];
        
        if(str[i] == str[len])
            len+=1;
        lps[i] = len; 
    }

    return lps;
}

// Application:
// 1. Given a text t and a string s, we want to find and display the positions of all occurrences of the string s in the text t.
// approach :- We generate the string s + # + t , where #  is a separator that appears neither in s nor in t. Let us calculate the prefix function for this string. now calculate how many times lps[i] == n when i >= n where n = length of string and m = length of pattern. eg https://www.spoj.com/problems/NAJPF/
// 2 Counting the number of occurrences of each prefix
// 3


// KMP algorithm
ll KMP_algo(string &text , string &pattern)
{
    ll n = text.length() , m = pattern.length(); 
    vector<ll> prefix = lps_generate(pattern);

    ll i = 0; // points to text 
    ll j = 0; // points to pattern
    while(i < n)
    {
        if(text[i] == pattern[j])
        {
            i+=1;
            j+=1;
        }
        else 
        {
            if(j != 0) j = prefix[j-1];
            else i+=1;
        }

        if(j == m)
        {
            return (i-m);
        }
    }
    return -1;
}

// string hashing :- in string hashing there is an hash function which will convert the string into an integer 
// means we are mapping an integer to each individual string ans then comparing this integers
// if s == t , then hash(s) == hash(t) but opposite is not true because we will mapping the string with fixed range of numbers
// However, in a wide majority of tasks, the probability of the hashes of two different strings colliding is still very small.
// this probability will depends on the value of mod 
// hash(str) = sigma(s[i]*p^i)%mod ,for all 0 <= i < n where p is power and mod is modulo value
// It is reasonable to make p as a prime number roughly equal to the number of characters in the input alphabet , when input character is lowercase than p may be 31
// Obviously mod should be a large number since the probability of two random strings colliding is about approx 1/mod.
// map character [a-z] with integers [1-26] , dont't start with zero because it will lead to a , aa , aaa , aaa... having same hash value

// Application:-
// 1. Search for duplicates string in the vector
// 2. Calulating the hash value for substring hash(str[i....j])  = (hash(str[0......j]) - hash(str[0....i-1]))*inv(p^i)
// 3. Rabin karp algorithm for pattern searching 
// 4. Number of different substring in O(n*n)
// 5. Calculate the number of pallindromic substring in the string

long long compute_hash(string &str) 
{
    long long p = 31;
    long long m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) 
    {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// Rabin Karp Algorithm: This algorithm is based on the concept of string hashing. Two strings pattern s and text t determine if the pattern appears in the text and if it does, enumerate all its occurrences in O(|s| + |t|)time.
// Algorithm: Calculate the hash for the pattern s.Calculate hash values for all the prefixes of the text t.Now, we can compare a substring of length |s| of t with s in constant time using the calculated hashes. So, compare each substring of length |s| with the pattern. This will take a total of O(|s| + |t|)

int main()
{
    freopen("zinput.txt","r",stdin);
    freopen("zoutput.txt","w",stdout);
    string text , pattern;
    cin >> text >> pattern;

    cout << KMP_algo(text , pattern) << endl;
    return 0;
}