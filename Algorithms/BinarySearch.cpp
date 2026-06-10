#include <bits/stdc++.h>
using namespace std;
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
