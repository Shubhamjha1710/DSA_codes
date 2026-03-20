#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <codecvt>
#include <complex>
#include <condition_variable>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <strstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

class SearchingStrategy
{
    int sz;
    vector<int> collection;

public:
    SearchingStrategy(vector<int> &nums)
    {
        this->collection = nums;
        this->sz = nums.size();
    }

    // Linear search strategy
    // T.C = O(n)
    void linearSearch(int element)
    {
        cout << "================ Linear Search ================" << endl;

        auto start = high_resolution_clock::now();

        int comparion_required = 0, idx = -1;
        for (int i = 0; i < sz; i++)
        {
            comparion_required += 1;
            if (collection[i] == element)
            {
                idx = i;
                break;
            }
        }

        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start);
        cout << "Comparion made      :" << comparion_required << endl;
        cout << "Element found at    :" << idx << endl;
        cout << "Time taken          :" << duration.count() << " microseconds" << endl;
        cout << "===============================================" << endl
             << endl;
    }

    // T.C = O(log(n))
    void binarySearch(int element)
    {
        cout << "================ Binary Search ================" << endl;

        auto start = high_resolution_clock::now();
        int comparion_required = 0;
        int low = 0, high = sz - 1, idx = -1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            comparion_required += 1;
            if (collection[mid] == element)
            {
                idx = mid;
                break;
            }
            else if (collection[mid] < element)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        cout << "Comparion made      :" << comparion_required << endl;
        cout << "Element found at    :" << idx << endl;
        cout << "Time taken          :" << duration.count() << " microseconds" << endl;
        cout << "===============================================" << endl
             << endl;
    }

    // Interpolation Search is an improved version of binary search that tries to
    // guess where the target value might be based on its value, instead of always
    // checking the middle.
    // In Binary Search, you always go to the middle.
    // In Interpolation Search, you go to a position proportional to the value.
    // Think of a dictionary if you search for “Zebra”, you don’t open the middle
    // you jump near the end. Best to use when elements are uniformly distributed
    // T.C O(log(n))
    void interpolationSearch(int element)
    {
        cout << "============ Interpolation Search =============" << endl;

        auto start = high_resolution_clock::now();
        int low = 0, high = sz - 1;
        int idx = -1, comparion_required = 0;

        while (low <= high)
        {
            int pos = low + ((double)(element - collection[low]) * (high - low)) / (collection[high] - collection[low]);
            comparion_required+=1;
            if (collection[pos] == element)
            {
                idx = pos;
                break;
            }
            else if (collection[pos] < element)
            {
                low = pos + 1;
            }
            else
            {
                high = pos - 1;
            }
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        cout << "Comparion made      :" << comparion_required << endl;
        cout << "Element found at    :" << idx << endl;
        cout << "Time taken          :" << duration.count() << " microseconds" << endl;
        cout << "===============================================" << endl
             << endl;
    }

    // Jump Search algorithm is a slightly modified version of the linear search
    // algorithm. The main idea behind this algorithm is to reduce the time complexity 
    // by comparing lesser elements than the linear search algorithm. The input array
    // is hence sorted and divided into blocks to perform searching while jumping
    // through these blocks. 
    // Optimal block size = sqrt(n)
    // T.C  O(sqrt(n))
    void jumpSearch(int element) {
        cout << "================ Jump Search ================" << endl;

        auto start = high_resolution_clock::now();

        int blockSize = sqrt(sz);
        int comparion_required = 0, idx = -1, block_st = 0;
        for (int i = 0; i < sz; i+=blockSize)
        {
            comparion_required += 1;
            if (collection[i] > element)
            {
                break;
            }
            block_st = i;
        }

        for(int i = block_st; i < sz; i++) {
            comparion_required+=1;
            if(collection[i] == element) {
                idx = i;
                break;
            }
        }

        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start);
        cout << "Comparion made      :" << comparion_required << endl;
        cout << "Element found at    :" << idx << endl;
        cout << "Time taken          :" << duration.count() << " microseconds" << endl;
        cout << "===============================================" << endl
             << endl;
    }

    // Exponential Search (also called doubling search) is used on sorted arrays. 
    // It quickly finds a range where the target might exist by growing the search 
    // window exponentially, and then applies Binary Search in that range.
    // Instead of searching the whole array start from index 1 keep doubling the
    // index and stop when you go beyond the size or arr[i] > target 
    // T.C : O(log(n))
    void exponentialSearch(int element) {
        cout << "============== Exponential Search ==============" << endl;

        auto start = high_resolution_clock::now();
        
        int comparison_required = 0, idx = -1;
        if(collection[0] == element) {
            idx = 0;
        } else {
            int i = 1;
            comparison_required += 1;
            while (i < sz && collection[i] <= element) {
                i *= 2;
            }

            int low = i/2, high = min(i, sz-1);
            while(low <= high) {
                int mid = (low+high)/2;
                comparison_required += 1;
                if(collection[mid] == element) {
                    idx = mid;
                    break;
                } else if(collection[mid] < element) {
                    low = mid+1;
                } else {
                    high = mid-1;
                }
            }
        }
        

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Comparion made      :" << comparison_required << endl;
        cout << "Element found at    :" << idx << endl;
        cout << "Time taken          :" << duration.count() << " microseconds" << endl;
        cout << "===============================================" << endl
             << endl;
    }
};

int main()
{
    int element = 1049056;
    vector<int> nums = {element};
    for (int i = 0; i < 20000000; i++)
    {
        nums.push_back(rand() % 10000000);
    }
    sort(nums.begin(), nums.end());

    SearchingStrategy *strategies = new SearchingStrategy(nums);
    strategies->linearSearch(element);
    strategies->binarySearch(element);
    strategies->interpolationSearch(element);
    strategies->jumpSearch(element);
    strategies->exponentialSearch(element);

    return 0;
}