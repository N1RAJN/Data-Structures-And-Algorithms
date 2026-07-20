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
    // NOTE: For index i, number of characters matched
    // on each side at center i
    vector<int> radius(n, 0);

    // NOTE: Exclusive borders (l, r) of the outer palindrome.
    int l = 0, r = 1;
    for (int i = 0; i < n; ++i) {
        if (i <= r)
            // WARN: Bound the length of palindrome to be within the borders of
            // outer palindrome. BECAUSE the symmetry of the inner palindromes
            // is only guaranteed within the outer palindromes
            radius[i] = min(r - i, radius[l + (r - i)]);

        // NOTE: If there exists a larger palindrome outside the outer border,
        // expand and update the outer border
        while (i - radius[i] - 1 >= 0 && i + radius[i] + 1 < n &&
               t[i - radius[i] - 1] == t[i + radius[i] + 1])
            radius[i]++;

        // NOTE: Update the outer border if expanded
        if (i + radius[i] > r) {
            l = i - radius[i];
            r = i + radius[i];
        }
    }
    // NOTE: The '#' occupy all the EVEN indices while the character from the
    // original string are at ODD indices in the radius array

    // WARN : The odd indices of radius array contain the LENGTH of the largest
    // palindrome at that index, not just number of character matched on each
    // side. BECAUSE the extra character '#', add twice the length on each side.

    // NOTE: Mapping of indices between original and pre-processed i.e, "s" &
    // "t" string
    // s -> t : i -> 2 * i + 1;
    return radius;
}
