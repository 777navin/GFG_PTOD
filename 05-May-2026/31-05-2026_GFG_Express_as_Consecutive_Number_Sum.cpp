/*
Date: 31-05-2026
Problem Name: Express as Consecutive Number Sum
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Math, Bit Manipulation, Number Theory

Problem Summary:
Given a number 'n', determine whether 'n' can be expressed as the sum of two or more consecutive positive numbers. 

Methods to Solve:
1. Better Approach (Mathematical Iteration)
2. Optimal Approach (Bitwise / Power of 2 Property)

-------------------------------------------------------------------------
Method 1: Better Approach (Mathematical Iteration)
-------------------------------------------------------------------------
- Intuition: 
  Let the sum of 'k' consecutive numbers starting from 'x' be n.
  x + (x+1) + (x+2) + ... + (x+k-1) = n
  k*x + [k*(k-1)]/2 = n
  k*x = n - [k*(k-1)]/2
  For 'x' to be a valid positive integer (x >= 1), the right side must be 
  strictly positive and perfectly divisible by 'k'.

- Approach:
  Iterate 'k' from 2 upwards as long as [k*(k-1)]/2 < n.
  Check if (n - [k*(k-1)]/2) % k == 0. If yes, return true.

- Dry Run (n = 10):
  k=2: n - (2*1)/2 = 10 - 1 = 9. 9 % 2 != 0
  k=3: n - (3*2)/2 = 10 - 3 = 7. 7 % 3 != 0
  k=4: n - (4*3)/2 = 10 - 6 = 4. 4 % 4 == 0 -> Returns true!

- Time Complexity: O(√n)
- Space Complexity: O(1)
- Why better than brute force: Avoids nested loops, checks mathematical validity directly.
- When to use: When you need the actual sequence length 'k', or if bitwise properties don't apply.

-------------------------------------------------------------------------
Method 2: Optimal Approach (Bitwise)
-------------------------------------------------------------------------
- Intuition:
  A known mathematical property states that a number can be expressed as a 
  sum of 2 or more consecutive positive integers IF AND ONLY IF it has at 
  least one odd prime factor. 
  The only numbers without any odd prime factors are powers of 2 (2^0, 2^1, 2^2...).
  Therefore, if 'n' is a power of 2, it CANNOT be expressed as such a sum.

- Approach:
  Use the bitwise AND trick to check if a number is a power of 2.
  For any power of 2, `n & (n - 1)` will evaluate to 0. 
  If it doesn't equal 0, it means 'n' is not a power of 2, so we return true.

- Dry Run (n = 10):
  10 in binary: 1010
  9 in binary:  1001
  10 & 9 = 1000 (8 in decimal). 8 != 0 -> Returns true.

- Time Complexity: O(1)
- Space Complexity: O(1)
- Why better than previous method: Constant time execution, single operation.
- When to use: Best for competitive programming due to O(1) efficiency.

Comparison Table:
Method             | TC      | SC   | Best Use Case
-------------------|---------|------|------------------------------------
Math Iteration     | O(√n)   | O(1) | When the sequence itself is needed
Bitwise (Optimal)  | O(1)    | O(1) | Checking boolean possibility only

Final Recommended Solution: Method 2 (Bitwise Optimal)
*/

#include <iostream>

using namespace std;

class Solution {
public:
    // Method 1: Mathematical Iteration
    bool isSumOfConsecutiveIterative(int n) {
        for (long long k = 2; k * (k - 1) / 2 < n; k++) {
            long long subtracted = n - (k * (k - 1) / 2);
            if (subtracted % k == 0) {
                return true;
            }
        }
        return false;
    }

    // Method 2: Optimal Approach (Bitwise) - Required GFG Format
    bool isSumOfConsecutive(int n) {
        // If n is NOT a power of 2, it can be expressed as sum of consecutive numbers.
        // n & (n - 1) is 0 only for powers of 2.
        return (n & (n - 1)) != 0;
    }
};

// Driver Code - To make the file standalone and runnable
int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            Solution obj;
            // Using the Optimal Approach
            bool ans = obj.isSumOfConsecutive(n);
            if (ans) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
    } else {
        // Example fallback for local testing if no multiple test cases are provided
        Solution obj;
        int testCases[] = {10, 8, 24};
        for(int test : testCases) {
            cout << "Input: " << test 
                 << " | Output: " << (obj.isSumOfConsecutive(test) ? "true" : "false") 
                 << "\n";
        }
    }

    return 0;
}
