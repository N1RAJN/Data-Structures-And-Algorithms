#include <bits/stdc++.h>
using namespace std;

void mergeArray(vector<int> &nums, int l, int m, int r) {
    int leftSize = m - l + 1, rightSize = r - m;
    int rightArr[rightSize], leftArr[leftSize];

    for (int i = 0; i < leftSize; i++) {
        leftArr[i] = nums[l + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightArr[j] = nums[m + j + 1];
    }

    int i = 0, j = 0, k = l;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] < rightArr[j])
            nums[k++] = leftArr[i++];
        else
            nums[k++] = rightArr[j++];
    }

    while (i < leftSize)
        nums[k++] = leftArr[i++];

    while (j < rightSize)
        nums[k++] = rightArr[j++];
}

void mergeSort(vector<int> &nums, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;

    mergeSort(nums, l, m);
    mergeSort(nums, m + 1, r);
    mergeArray(nums, l, m, r);
}
