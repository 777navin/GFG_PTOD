/*
Date: 20-05-2026
Problem Name: Product Pair
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Array, Hashing, Math

Problem Summary:
Given an array of integers arr[] and an integer target, find if there exists a pair of elements in the array whose product is exactly equal to the target. Return true if found, otherwise false.

Methods to Solve:
1. Brute Force
2. Optimal Approach (Hashing)

For EACH method include:

Method 1: Brute Force
- Intuition: The simplest way is to check all possible pairs in the array to see if their product matches the target.
- Approach: Use two nested loops. The outer loop picks the first element, and the inner loop picks the second element from the remaining array. Multiply them and check against the target.
- Dry Run: arr = [10, 20, 9, 40], target = 400
  i = 0 (10), j = 1 (20) -> 10 * 20 = 200 != 400
  i = 0 (10), j = 3 (40) -> 10 * 40 = 400 == target -> return true
- Time Complexity: O(N^2), where N is the number of elements.
- Space Complexity: O(1), no extra space used.
- Why better than previous method: N/A (Baseline)
- When to use: Only when the array size is extremely small (N <= 10^3) or extra space is strictly prohibited.

Method 2: Optimal Approach (Hashing)
- Intuition: Instead of looking ahead for a matching pair, we can look backward. As we traverse the array, we can check if the required multiplier to reach the target has already been seen.
- Approach: Use an unordered_set to keep track of visited elements. For each element 'num':
  1. If 'num' is 0, we check if target is also 0. If so, return true.
  2. If 'num' is not 0, check if target is perfectly divisible by 'num' (target % num == 0). If it is, check if the complement (target / num) exists in our set. 
  3. Insert the current 'num' into the set.
- Dry Run: arr = [-10, 0, 9, -40], target = 0
  i=0, num=-10: target%num == 0, complement = 0. Set is empty. Insert -10. Set={-10}
  i=1, num=0: num==0 and target==0 -> return true. 
- Time Complexity: O(N) on average, as unordered_set lookups and insertions take O(1) time on average.
- Space Complexity: O(N) to store the elements in the hash set.
- Why better than previous method: Drastically reduces the time complexity from Quadratic to Linear.
- When to use: Always recommended for large constraints like N = 10^5.

Comparison Table:
Method         | TC       | SC      | Best Use Case
------------------------------------------------------------
Brute Force    | O(N^2)   | O(1)    | Space constrained environments.
Optimal (Hash) | O(N)     | O(N)    | Standard scalable solution for large inputs.

Final Recommended Solution: Method 2 (Optimal Approach using Hashing)
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    // Method 1: Brute Force Approach
    bool isProductBruteForce(vector<int>& arr, long long target) {
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Cast to long long to prevent integer overflow during multiplication
                if (1LL * arr[i] * arr[j] == target) {
                    return true;
                }
            }
        }
        return false;
    }

    // Method 2: Optimal Approach (Final Recommended Solution)
    bool isProduct(vector<int>& arr, long long target) {
        unordered_set<long long> seenElements;

        for (int num : arr) {
            // Edge case: current number is 0
            if (num == 0) {
                if (target == 0) {
                    return true;
                }
            } 
            else {
                // If target is perfectly divisible by num, check for the required complement
                if (target % num == 0) {
                    long long requiredComplement = target / num;
                    if (seenElements.count(requiredComplement)) {
                        return true;
                    }
                }
            }
            // Mark current number as seen
            seenElements.insert(num);
        }

        return false;
    }
};

// Driver code for standalone execution and testing
int main() {
    // Optimize standard I/O operations for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;

    // Test Case 1
    vector<int> arr1 = {10, 20, 9, 40};
    long long target1 = 400;
    cout << "Test Case 1: " << (sol.isProduct(arr1, target1) ? "True" : "False") << "\n";

    // Test Case 2
    vector<int> arr2 = {-10, 20, 9, -40};
    long long target2 = 30;
    cout << "Test Case 2: " << (sol.isProduct(arr2, target2) ? "True" : "False") << "\n";

    // Test Case 3
    vector<int> arr3 = {-10, 0, 9, -40};
    long long target3 = 0;
    cout << "Test Case 3: " << (sol.isProduct(arr3, target3) ? "True" : "False") << "\n";

    return 0;
}
