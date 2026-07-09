#include <bits/stdc++.h>
using namespace std;

vector<int> manacher(string s) {
    // NOTE: Pre-process string to handle palindromes of
    // different parities easily.
    // 1. Odd palindromes will still be centered at their original center.
    // 2. Even palindromes will now be centered at '#'.
    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }

    int n = t.size();
    // NOTE: Sentinals values at two ends to avoid dealing with ends of string
    // separately
    t = "$" + t + "^";

    // NOTE: For index i, number of characters matched
    // on each side at center i
    vector<int> diameter(n + 2, 0);

    // NOTE: Exclusive borders (l, r) of the outer palindrome.
    int l = 0, r = 1;
    for (int i = 1; i <= n; ++i) {
        int mirrorI = l + (r - i);

        if (i <= r)
            // NOTE: Bound the length of palindrome to be within the borders of
            // outer palindrome. BECAUSE the symmetry of the inner palindromes
            // is only guaranteed within the outer palindromes
            diameter[i] = min(r - i, diameter[mirrorI]);

        // NOTE: If there exists a larger palindrome outside the outer border,
        // expand and update the outer border
        while (t[i - diameter[i] - 1] == t[i + diameter[i] + 1])
            diameter[i]++;

        // NOTE: Update the outer border if expanded
        if (i + diameter[i] > r) {
            l = i - diameter[i];
            r = i + diameter[i];
        }
    }
    return vector<int>(begin(diameter) + 1, end(diameter) - 1);
}
