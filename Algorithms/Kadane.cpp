#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int kadane(vector<int> &nums) {
    if (nums.empty())
        return 0;
    int maxSum = nums[0];
    int currSum = 0;
    for (int i : nums) {
        currSum = max(currSum, 0);
        currSum += i;
        maxSum = max(currSum, maxSum);
    }
    return maxSum;
}

pair<int, int> kadanePointers(vector<int> &nums) {
    if (nums.empty())
        return {};
    int l = 0;
    int maxSum = nums[l];
    int currSum = 0;
    int maxL = 0, maxR = 0;
    for (int r = 0; r < nums.size(); ++r) {
        if (currSum < 0) {
            currSum = 0;
            l = r;
        }
        currSum += nums[r];
        if (currSum > maxSum) {
            maxSum = currSum;
            maxL = l;
            maxR = r;
        }
    }
    return {maxL, maxR};
}
