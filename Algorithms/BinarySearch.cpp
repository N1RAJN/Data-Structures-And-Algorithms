#include <bits/stdc++.h>
using namespace std;

// NOTE: Classic Binary Search
// Search for PRESENCE of a certain item.
int binarySearch(vector<int> &nums, int k) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;

        if (nums[m] == k)
            return k;
        else if (nums[m] > k)
            r = m - 1;
        else
            l = m + 1;
    }

    return -1;
}

// NOTE: A general way to think about binary search is the finding pivot point
// from false to true or vice versa for some condition
// Eg. [F, F, F, F, F, T, T, T, T]
// Lower and Upper bound just dictate does equality (E in the following example)
// fall in the false or true region

// NOTE: Way to think about upper and lower bounds.
// Say for an array. F = less than, E = equal to, T = greater than
// Eg. [F, F, F, F, F, E, E, E, E, T, T, T, T]
//                     |           |
//                  Lower Bound    Upper Bound
// [Lower Bound, Upper Bound) : range of certain condition
// (in this case equality)

// NOTE: LowerBound, i.e, first index i, such that nums[i] >= x
int binarySearchLowerBound(vector<int> &nums, int k) {
    int l = 0, r = nums.size();
    while (l < r) {
        int m = l + (r - l) / 2;

        if (nums[m] >= k)
            r = m;
        else
            l = m + 1;
    }
    return l;
}

// NOTE: UpperBound, i.e, first index i, such that nums[i] > x
int binarySearchUpperBound(vector<int> &nums, int k) {
    int l = 0, r = nums.size();
    while (l < r) {
        int m = l + (r - l) / 2;

        if (nums[m] > k)
            r = m;
        else
            l = m + 1;
    }
    return l;
}
