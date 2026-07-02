#include <bits/stdc++.h>
using namespace std;

vector<int> manacher(string s) {
    // Pre-process string to handle odd and even length palindromes easily
    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }

    int n = t.size();
    // Sentinals values at two ends to avoid dealing with ends of string
    // separately
    t = "$" + t + "^";
    vector<int> palinCount(n + 2, 0);

    // NOTE: Exclusive borders (l, r) of the outer palindrome.
    int l = 0, r = 1;
    for (int i = 1; i <= n; ++i) {
        int mirrorI = l + (r - i);

        if (i <= r)
            // Bound the length of palindrome to be within the borders of outer
            // palindrome.
            palinCount[i] = min(r - i, palinCount[mirrorI]);

        // If there exists a larger palindrome outside the outer border, expand
        // and update the outer border
        while (t[i - palinCount[i] - 1] == t[i + palinCount[i] + 1])
            palinCount[i]++;

        if (i + palinCount[i] > r) {
            l = i - palinCount[i];
            r = i + palinCount[i];
        }
    }
    return vector<int>(begin(palinCount) + 1, end(palinCount) - 1);
}
