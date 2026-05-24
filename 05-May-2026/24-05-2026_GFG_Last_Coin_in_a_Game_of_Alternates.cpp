/*
Date: 24-05-2026
Problem Name: Last Coin in a Game of Alternates
Platform: GeeksforGeeks
Difficulty: Basic
Tags: Array, Two Pointers, Greedy, Simulation

Problem Summary:
Two players play a game picking coins alternately from either the beginning or the end of an array.
Both follow a greedy strategy, meaning they always pick the coin with the maximum value among the two available ends.
The game stops when exactly one coin is left. The task is to find the value of this last remaining coin.

Methods to Solve:
1. Brute Force (Array Modification)
2. Optimal Approach (Two Pointers)

=========================================================
1. Brute Force (Array Modification)
- Intuition: Simulate the game strictly by physically removing the chosen elements from the array until one element remains.
- Approach: Compare `arr.front()` and `arr.back()`. Remove the larger of the two using the `erase` or `pop_back` operations. Repeat until `arr.size() == 1`.
- Dry Run (small example): arr = [5, 3, 1, 6, 9]
  - Ends are 5 and 9. Pick 9. Erase 9. arr = [5, 3, 1, 6]
  - Ends are 5 and 6. Pick 6. Erase 6. arr = [5, 3, 1]
  - Ends are 5 and 1. Pick 5. Erase 5. arr = [3, 1]
  - Ends are 3 and 1. Pick 3. Erase 3. arr = [1]. Loop ends.
- Time Complexity: O(N^2) in the worst case, because erasing an element from the front of a `std::vector` requires shifting all subsequent elements, taking O(N) time per turn.
- Space Complexity: O(1) if done in place, but highly inefficient in time.
- Why better than previous method: N/A
- When to use: Never recommended for large inputs due to O(N^2) time complexity.

=========================================================
2. Optimal Approach (Two Pointers)
- Intuition: Instead of modifying the array (which is costly), we can simply use two pointers to represent the current "start" and "end" of the available coins. We shrink the window based on the greedy choices until the pointers meet.
- Approach:
  1. Initialize `left = 0` and `right = arr.size() - 1`.
  2. Run a `while (left < right)` loop.
  3. Compare `arr[left]` and `arr[right]`.
  4. If `arr[left] >= arr[right]`, increment the `left` pointer (simulating picking the left coin).
  5. Else, decrement the `right` pointer (simulating picking the right coin).
  6. When the loop terminates (`left == right`), `arr[left]` will be the last remaining coin.
- Dry Run (small example): arr = [5, 9, 2, 5]
  - left = 0 (val 5), right = 3 (val 5). Both are equal, pick left. left = 1.
  - left = 1 (val 9), right = 3 (val 5). 9 > 5, pick left. left = 2.
  - left = 2 (val 2), right = 3 (val 5). 5 > 2, pick right. right = 2.
  - left = 2, right = 2. Loop breaks. Return arr[2] = 2.
- Time Complexity: O(N) because each step moves a pointer by 1. The loop runs exactly N-1 times.
- Space Complexity: O(1) as no extra space is used; we only use integer variables.
- Why better than previous method: Completely eliminates the O(N) shifting overhead, reducing the total time complexity to linear O(N).
- When to use: Always. This is the most optimal way to solve the problem and perfectly satisfies the given constraints.

Comparison Table:
Method             | TC     | SC   | Best Use Case
-------------------|--------|------|--------------------------------------
Brute Force        | O(N^2) | O(1) | Small arrays (N <= 1000)
Optimal Approach   | O(N)   | O(1) | All standard and edge cases (N = 10^5)

Final Recommended Solution: Optimal Approach (Two Pointers)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int coin(vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;
        
        // Loop runs until only one coin is left in our pointer window
        while (left < right) {
            // Both players follow a greedy strategy to pick the maximum coin
            if (arr[left] >= arr[right]) {
                left++;  // Pick the left coin
            } else {
                right--; // Pick the right coin
            }
        }
        
        // The pointers have met, pointing to the last remaining coin
        return arr[left];
    }
};

// ==========================================
// Driver Code for Local Testing
// ==========================================
int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Hardcoded test cases simulating the platform's behavior
    Solution obj;
    
    vector<int> test1 = {5, 3, 1, 6, 9};
    cout << "Test Case 1 Output: " << obj.coin(test1) << " | Expected: 1\n";
    
    vector<int> test2 = {5, 9, 2, 5};
    cout << "Test Case 2 Output: " << obj.coin(test2) << " | Expected: 2\n";
    
    vector<int> test3 = {11};
    cout << "Test Case 3 Output: " << obj.coin(test3) << " | Expected: 11\n";

    return 0;
}
