#include <bits/stdc++.h>
using namespace std;
#define ll long long
// stable sorting algo : bubble , merge , insertion , count sort
// unstable sorting algo : heap , Quick sort

// Bubble Sort
// tc = O(n*n) , sc= O(1)
// at each pass ith largest element takes n-i position
vector<ll> bubbleSort(vector<ll> &vt , ll n)
{
    for(ll i = 0; i < n-1;i++)
    {
        for(ll j = 0; j < n-i-1;j++)
        {
            if(vt[j] > vt[j+1]) swap(vt[j], vt[j+1]);
        }
    }
    return vt;
}

// insertion sort 
// tc = O(n*n) , sc = O(1)
// at each step we have some sorted part of array and some unsorted part and every iteration we move an element from unsorted to sorted part
// It can also be useful when the input array is almost sorted, and only a few elements are misplaced in a complete big array.
vector<ll> insertion(vector<ll> &vt , ll n)
{
    for(ll i = 1;i<n;i++)
    {
        ll key =  vt[i];
        ll j = i-1;

        while(j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j]
            j-=1;
        }
        vt[j+1] = key;
    }
    return vt;
} 

// Selection Sort
// tc = O(n*n) , sc = O(1)
// Selection sort is a simple and efficient sorting algorithm that works by repeatedly selecting the smallest (or largest) element from the unsorted portion of the list and swap it with first element of sorted portion of the list. 
// to make selection sort stable , instead of swaping the first element with the minimum shift all element by 1 till minimum and put that minimum element at first
vector<ll> selection(vector<ll> &vt , ll n)
{
    ll mni = 0;
    for(ll i = 0; i < n; i++)
    {
        ll idx = i;
        for(ll j = i+1; j < n; j++)
        {
            if(vt[j] < vt[idx])
            {
                idx = j;
            }
        }
        swap(vt[idx] , vt[i]);
    }
}

// stable selection sort 
vector<ll> stable_selection(vector<ll> &vt , ll n)
{
    for(ll i = 0; i < n; i++)
    {
        ll idx = i;
        for(ll j = i+1; j < n; j++)
        {
            if(vt[j] < vt[idx]) idx = j;
        }

        ll mni = vt[idx];
        for(ll j = idx;j>i;j--) vt[j] = vt[j-1];
        vt[i] = key;
    }
}

// merge sort 
// in merge sort is to divide the array into two halves, sort each half, and then merge the sorted halves back together. This process is repeated until the entire array is sorted.
// one main advantage of merge sort is its nlogn tc and parallizing capacity
// tc = O(nlogn) , sc = O(nlogn)

void merge(vector<ll> &vt , ll left , ll mid , ll right)
{
    vector<ll> sorted(right+1);
    ll i = left , j = mid+1 , k = 0;
    while(i <= mid && j <= right)
    {
        if(arr[i] < arr[j]) sorted[k++] = arr[i++];
        else sorted[k++] = arr[j++]
    }
    while(i <= mid) sorted[k++] = arr[i++];
    while(j <= right) sorted[k++] = arr[j++];
    for(ll i = left;i<right;i++) arr[i] = sorted[i];
}

void mergeSort(vector<ll> &vt , ll left , ll right)
{
    if(left >= right) return;

    ll mid = left + (right-left)/2;
    mergeSort(arr , left , mid);
    mergeSort(arr , mid+1 , right);
    merge(arr , left , mid , right);
}

// inversion count
ll merged(vector<ll> &vt , ll left , ll right , ll mid)
{
    ll inversion = 0;
    vector<ll> sorted(right+1);
    ll i = left , j = mid+1 , k = 0;
    while(i <= mid && j <= right)
    {
        if(arr[i] <= arr[j]) sorted[k++] = arr[i++];  // if we use this <= in sorting algorithm this will make it unstable sort
        else 
        {
            sorted[k++] = arr[j++];
            inversion += (mid-i+1);
        }
    }
    while(i <= mid) sorted[k++] = arr[i++];
    while(j <= right) sorted[k++] = arr[j++];
    for(ll i = left;i<right;i++) arr[i] = sorted[i];
}
ll mergeSort(vector<ll> &vt , ll left , ll right)
{
    if(left >= right) return 0;

    ll inversion = 0;
    ll mid = left + (right-left)/2;
    inversion += mergeSort(arr , left , mid);
    inversion += mergeSort(arr , mid+1 , right);
    inversion += merge(arr , left , mid , right);
    return inversion;
}


// Quick Sort
// QuickSort is a sorting algorithm that is based on the Divide and Conquer algorithm parddigm in which we picks an element as a pivot and partitions the given array around the picked pivot by placing the pivot in its correct position in the sorted array.
// there is 3 ways of choosing a pivot element 
// 1. pick always first element as pivot element
// 2. pick always second element as pivot element
// 3. pick random element as pivot

// partition function when pick last element as pivot
ll partition(vector<ll> &vt , ll low , ll high)
{
    ll pivot = vt[high];
    ll idx =  low;
    for(ll i = low;i<high;i++)
    {
        if(vt[i] < pivot)
        {
            swap(vt[idx] , vt[i]);
            idx+=1;
        }
    }

    swap(vt[idx] , vt[high]);
    return idx;
}

// when pick first element as pivot
ll partition(vector<ll> &vt , ll low , ll high)
{
    ll pivot = vt[low];
    ll idx = high;
    for(ll i = high; i > low; i--)
    {
        if(vt[i] > pivot)
        {
            swap(vt[i] , vt[idx]);
            idx-=1;
        }
    }
    swap(vt[idx] , vt[low]);
    return idx;
}


void quickSort(vector<ll> &vt , ll low , ll high)
{
    if(low >= high) return;
    ll mid = (low + high) / 2;
    ll idx = partition(vt, low, mid);
    quickSort(vt, low , idx-1);
    qucikSort(vt, idx+1 , high);
}

// Heap Sort
// First convert the array into max heap using heapify, then one by one delete the root node of the max heap and replace it with the last node in the heap and then heapify the root of the heap.
// this is unstable sorting algortihm
// tc = O(nlogn) sc = O(1)

// function for making subtree of node idx as heap
// in heapify algo we try to make subtree of idx as heap when and left and right subtree of idx is already a heap
void heapify(vector<ll> &arr , ll n  , ll idx)
{
    ll largest = i;
    ll left = 2*idx+1 , right = 2*idx+2;
    if(left < n && arr[left] > arr[right]) largest = left;
    if(right < n && arr[right] > arr[largest]) largest = right

    if(largest != i)
    {
        swap(arr[i] , arr[largest]);
        heapify(arr , n , largest);
    }
}

void heapSort(vector<ll> &arr , ll n)
{
    for(ll i = n/2;i>=0;i--) heapify(arr , n , i);

    // heapsort
    for(ll i = n-1;i>=0;i--)
    {
        swap(arr[0] , arr[i]);
        heapify(arr , i , 0); // heapify for remaining n-1 elements
    }
}

// counting sort
// Counting sort is a sorting technique based on keys between a specific range. It works by counting the number of objects having distinct key values (a kind of hashing). 
// for sorting the string count sort algo is very efficient algo
vector<ll>  countSort(vector<ll> &arr , ll n , ll range)
{
    vector<ll> sorted(n ,0);
    vector<ll> count(range+1);
    for(ll i = 0;i<n;i++) count[arr[i]]+=1;

    for(ll i = 1;i<=range;i++) count[i]+=count[i-1];
    
    // for stable sorting
    for(ll i = n-1;i>=0;i--)
    {
        sorted[count[arr[i]-1]] = arr[i];
        count[arr[i]]-=1;
    }
    return sorted;
}

// radix sort
// Radix Sort is a linear sorting algorithm that sorts elements by processing them digit by digit. It is an efficient sorting algorithm for integers or strings with fixed-size keys

vector<ll> radixSort(vector<ll> &vt , ll n)
{
    ll mxi = 0;
    for(ll i = 0;i<n;i++) mxi =  max(mxi , vt[i]);
    
    ll digit = digit_count(mxi);
    ll weight = 10;
    for(ll k = 0;k<mxi;k++)
    {
        vector<ll> hash(10 , 0);
        for(ll i = 0;i<n;i++) hash[vt[i]%10]+=1;
        for(ll i = 1;i<10;i++) hash[i] += hash[i-1];

        vector<ll> sorted(n , 0);
        for(ll i = n-1;i>=0;i--)
        {
            sorted[(hash[vt[i]])%weight-1] = vt[i];
            hash[(vt[i])%weight]-=1;
        }

        vt = sorted;
    }
    return vt;
}