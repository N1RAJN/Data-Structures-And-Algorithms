#include <bits/stdc++.h>
using namespace std;
int partition(vector<int> &nums, int l, int r) {
    int pIdx = l - 1;
    int temp;
    for (int i = l; i < r; ++i) {
        if (nums[i] < nums[r]) {
            pIdx++;
            temp = nums[i];
            nums[i] = nums[pIdx];
            nums[pIdx] = temp;
        }
    }
    pIdx++;
    temp = nums[r];
    nums[r] = nums[pIdx];
    nums[pIdx] = temp;
    return pIdx;
}

void quickSort(vector<int> &nums, int l, int r) {
    if (l >= r)
        return;
    int m = partition(nums, l, r);
    quickSort(nums, l, m - 1);
    quickSort(nums, m + 1, r);
}
