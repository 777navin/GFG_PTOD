// 01-06-2026_GFG_Max_Product_Subset.cpp

/*
Date: 01-06-2026
Problem Name: Max Product Subset
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Arrays, Greedy, Mathematical, Modulo Arithmetic

Problem Summary:
Given an array `arr[]`, find and return the maximum product possible with the subset 
of elements present in the array. Since the product can be large, return it modulo 10^9 + 7.
The maximum product can be of a single element also.

Methods to Solve:
1. Brute Force
2. Optimal Approach (Greedy)

For EACH method include:

---------------------------------------------------------
Method 1: Brute Force
---------------------------------------------------------
- Intuition: Generate all possible non-empty subsets of the array, calculate the 
  product of each subset, and keep track of the maximum product encountered.
- Approach: Use recursion (pick / not pick) to generate $2^N - 1$ subsets.
- Dry Run: 
  arr = [-1, 0, -2]
  Subsets: {-1}, {0}, {-2}, {-1, 0}, {-1, -2}, {0, -2}, {-1, 0, -2}
  Products: -1, 0, -2, 0, 2, 0, 0
  Max Product: 2
- Time Complexity: $O(2^N)$ - Exponential time to generate all subsets.
- Space Complexity: $O(N)$ - For the recursive call stack.
- Why better than previous method: N/A (Baseline).
- When to use: Only useful for very small array sizes ($N \le 15$).

---------------------------------------------------------
Method 2: Optimal Approach (Greedy)
---------------------------------------------------------
- Intuition: To maximize a product:
  - Zeros will ruin the product, so we ignore them.
  - Positive numbers always increase the magnitude, so include all of them.
  - Negative numbers multiply to a positive number in pairs. Thus, if there are an 
    even number of negatives, we include all of them. If there is an odd number of 
    negatives, we must exclude exactly one negative number. To maximize the remaining 
    product, we exclude the negative number with the smallest absolute value 
    (i.e., the largest negative number, closest to 0).
- Approach:
  1. Base case: If $N = 1$, return the single element.
  2. Count zeros and negative numbers, and find the maximum negative number (`max_neg`).
  3. Edge case A: If all elements are zero, return 0.
  4. Edge case B: If there is exactly 1 negative number and all other elements are zero, return 0.
  5. Traverse the array again and multiply elements to `prod`. Skip zeros.
  6. If the count of negatives is odd, skip the `max_neg` exactly once.
  7. Handle modulo arithmetic at each multiplication step.
- Dry Run:
  arr = [-1, 0, -2, 4, 3]
  Counts: zeros = 1, negs = 2. max_neg = -1.
  Since negs is even (2), we include all negatives.
  prod = (-1 * -2 * 4 * 3) = 24.
- Time Complexity: $O(N)$ - Two linear passes through the array.
- Space Complexity: $O(1)$ - Only using a few scalar variables for counting and tracking.
- Why better than previous method: Drastically reduces time complexity from exponential to linear.
- When to use: Recommended for all competitive programming and interview environments.

Comparison Table:
Method       | TC       | SC     | Best Use Case
---------------------------------------------------
Brute Force  | O(2^N)   | O(N)   | Concept building, tiny constraints
Optimal      | O(N)     | O(1)   | Standard large constraints (N <= 20,000)

Final Recommended Solution: Method 2 (Greedy Approach)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxProduct(vector<int>& arr) {
        int n = arr.size();
        
        // Base Case: Only 1 element
        if (n == 1) {
            return arr[0];
        }

        long long mod = 1e9 + 7;
        int max_neg = INT_MIN;
        int count_zero = 0;
        int count_neg = 0;

        // Step 1: Count zeros, negatives, and find the largest negative number
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) {
                count_zero++;
            } else if (arr[i] < 0) {
                count_neg++;
                max_neg = max(max_neg, arr[i]);
            }
        }

        // Edge Case A: All zeros
        if (count_zero == n) {
            return 0;
        }

        // Edge Case B: One negative number and everything else is zero
        if (count_neg == 1 && count_zero == n - 1) {
            return 0;
        }

        long long prod = 1;
        bool skipped_max_neg = false;

        // Step 2: Calculate the product
        for (int i = 0; i < n; i++) {
            // Ignore zeros
            if (arr[i] == 0) {
                continue;
            }
            
            // If odd number of negatives, skip the largest negative once
            if (count_neg % 2 != 0 && arr[i] == max_neg && !skipped_max_neg) {
                skipped_max_neg = true;
                continue;
            }
            
            // Multiply and handle modulo
            prod = (prod * (long long)arr[i]) % mod;
        }

        // C++ modulo operator on negative numbers yields negative result.
        // We adjust it to strictly positive representation if necessary.
        if (prod < 0) {
            prod = (prod % mod + mod) % mod;
        }

        return (int)prod;
    }
};

// Driver Code for Local Testing (GeeksforGeeks Format)
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cout << "Enter number of test cases: ";
    if (cin >> t) {
        while (t--) {
            int n;
            cout << "Enter array size: ";
            cin >> n;
            
            vector<int> arr(n);
            cout << "Enter array elements: ";
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            
            Solution obj;
            long long ans = obj.findMaxProduct(arr);
            cout << "Max Product Subset is: " << ans << "\n";
        }
    } else {
        // Quick run with the example from the problem screenshot
        Solution obj;
        vector<int> arr1 = {-1, 0, -2, 4, 3};
        cout << "Example 1 Output: " << obj.findMaxProduct(arr1) << " (Expected: 24)\n";
        
        vector<int> arr2 = {-1, 0};
        cout << "Example 2 Output: " << obj.findMaxProduct(arr2) << " (Expected: 0)\n";
        
        vector<int> arr3 = {5};
        cout << "Example 3 Output: " << obj.findMaxProduct(arr3) << " (Expected: 5)\n";
    }

    return 0;
}
