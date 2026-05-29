/*
Date: 29-05-2026
Problem Name: Count Sorted Digit Groupings
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Dynamic Programming, Recursion, Strings

Problem Summary:
Given a string 's' consisting of digits, split it into contiguous substrings such that the sum of the digits in each sub-group forms a non-decreasing sequence from left to right. Determine the total number of such valid groupings.

Methods to Solve:
1. Brute Force (Simple Recursion)
2. Optimal Approach (Recursion + Memoization / Top-Down DP)

-------------------------------------------------------------------
1. Brute Force (Simple Recursion)
-------------------------------------------------------------------
- Intuition: 
  At every index, we can form a substring by picking consecutive digits. We need to explore all possible partition points and keep track of the sum of the current partition. If this sum is greater than or equal to the previous partition's sum, we recursively check the rest of the string.

- Approach:
  - Create a recursive function `solve(idx, prev_sum)`.
  - Loop from `idx` to the end of the string, maintaining a `curr_sum`.
  - Whenever `curr_sum >= prev_sum`, make a recursive call to `solve(i + 1, curr_sum)`.
  - Base case: If we reach the end of the string, return 1 (representing one valid grouping).

- Dry Run (small example): 
  s = "12"
  solve(0, 0):
  - i=0, curr_sum = 1 ("1"). 1 >= 0 -> solve(1, 1)
    - Inside solve(1, 1): i=1, curr_sum = 2 ("2"). 2 >= 1 -> solve(2, 2)
      - Inside solve(2, 2): idx == length -> returns 1.
  - i=1, curr_sum = 3 ("12"). 3 >= 0 -> solve(2, 3)
    - Inside solve(2, 3): idx == length -> returns 1.
  Total = 1 + 1 = 2.

- Time Complexity: O(2^N) in the worst case as we explore all possible partitions.
- Space Complexity: O(N) for the recursive call stack.
- Why better than previous method: N/A (Baseline).
- When to use: Only for very small string lengths (e.g., N <= 20).

-------------------------------------------------------------------
2. Optimal Approach (Recursion + Memoization / Top-Down DP)
-------------------------------------------------------------------
- Intuition: 
  The brute force approach computes the same subproblems repeatedly. For instance, the number of valid groupings from index `i` with a specific `prev_sum` doesn't change. We can cache these results in a 2D DP array.

- Approach:
  - The maximum length of the string is 100.
  - The maximum possible sum of a substring is 100 * 9 = 900.
  - Create a `dp[105][905]` initialized with -1.
  - In our recursive function `solve(idx, prev_sum)`, check if `dp[idx][prev_sum]` is already computed. If so, return it.
  - Otherwise, compute the ways, store it in `dp[idx][prev_sum]`, and return.

- Dry Run (small example):
  (Similar to Brute Force, but results are saved in `dp[][]` before returning, avoiding redundant recursive tree branches if the same `idx` and `prev_sum` are encountered again).

- Time Complexity: O(N^2) 
  There are N * 900 states, and for each state, we run a loop of max size N. Total operations roughly N * N * 900, which easily passes within 1 second for N = 100.
- Space Complexity: O(N * MaxSum) 
  `dp` array takes 105 * 905 * 4 bytes ≈ 380 KB + O(N) auxiliary recursion stack space.
- Why better than previous method: Reduces exponential time complexity to polynomial time, preventing Time Limit Exceeded (TLE).
- When to use: Always optimal for constraints up to N = 100.

-------------------------------------------------------------------
Comparison Table:
Method       | TC       | SC           | Best Use Case
-------------------------------------------------------------------
Brute Force  | O(2^N)   | O(N)         | N <= 20
Optimal (DP) | O(N^2)   | O(N*MaxSum)  | Default/Competitive Coding

Final Recommended Solution: Optimal Approach (Recursion + Memoization)
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Solution {
private:
    // Max length is 100, Max possible sum is 100 * 9 = 900
    int dp[105][905];

    int solve(int idx, int prev_sum, const string& s) {
        // Base case: successfully reached the end of the string
        if (idx == s.length()) {
            return 1;
        }

        // Return cached result if already computed
        if (dp[idx][prev_sum] != -1) {
            return dp[idx][prev_sum];
        }

        int ways = 0;
        int curr_sum = 0;

        // Try all contiguous substrings starting from current index
        for (int i = idx; i < s.length(); ++i) {
            curr_sum += (s[i] - '0');

            // Subgroup is valid if its sum is non-decreasing compared to the previous
            if (curr_sum >= prev_sum) {
                ways += solve(i + 1, curr_sum, s);
            }
        }

        // Cache and return
        return dp[idx][prev_sum] = ways;
    }

public:
    int validGroups(string &s) {
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, s);
    }
};

// Driver code for local testing and competitive programming
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    // Read number of test cases if input is provided via stdin
    if (cin >> t) {
        while (t--) {
            string s;
            cin >> s;
            Solution obj;
            cout << obj.validGroups(s) << "\n";
        }
    } else {
        // Default execution block if no stdin is provided (useful for quick local runs)
        Solution obj;
        
        string test1 = "1119";
        cout << "Input: " << test1 << "\n";
        cout << "Output: " << obj.validGroups(test1) << "\n\n";
        
        string test2 = "12";
        cout << "Input: " << test2 << "\n";
        cout << "Output: " << obj.validGroups(test2) << "\n";
    }

    return 0;
}
