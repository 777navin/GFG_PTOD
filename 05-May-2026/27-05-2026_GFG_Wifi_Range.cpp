// 27-05-2026_GFG_Wifi_Range.cpp

/*
Date: 27-05-2026
Problem Name: Wifi Range
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Strings, Array, Greedy, Two Pointers

Problem Summary:
Given a binary string `s` of length `n` representing rooms in a hostel (where '1' means a WiFi 
router is present, and '0' means no WiFi), and an integer `x` representing the range of each 
router. A router can cover `x` rooms to its left and `x` rooms to its right. We need to determine 
if every single room is covered by at least one WiFi router.

Methods to Solve:
1. Brute Force (Iterative Marking)
2. Difference Array / Line Sweep Algorithm
3. Optimal Approach (Gap Counting / Two Pointers)

======================================================================================
1. Brute Force
======================================================================================
- Intuition: For every WiFi router found ('1'), manually mark all rooms within its range 
  as covered in a separate boolean array. 
- Approach: Create a boolean array `visited` initialized to false. Iterate through `s`. 
  Whenever `s[i] == '1'`, iterate from `max(0, i - x)` to `min(n - 1, i + x)` and mark 
  `visited[j] = true`. Finally, check if any room is false.
- Dry Run: s = "10010", x = 1
  i=0 ('1'): marks index 0, 1
  i=3 ('1'): marks index 2, 3, 4
  All marked. Returns true.
- Time Complexity: O(N * X) in worst case (overlapping coverages repeatedly checked).
- Space Complexity: O(N) for the visited array.
- Why better than previous: N/A.
- When to use: When N and X are extremely small, and quick implementation is prioritized.

======================================================================================
2. Better Approach (Difference Array / Line Sweep)
======================================================================================
- Intuition: Instead of repeatedly marking elements in a range, we can use a difference 
  array to mark boundaries and then use a prefix sum to determine coverage.
- Approach: Create `diff` array of size `n + 1`. For every `s[i] == '1'`, increment 
  `diff[max(0, i - x)]` by 1, and decrement `diff[min(n, i + x + 1)]` by 1. Keep a 
  running sum while iterating over the array. If at any point running sum <= 0, that 
  room isn't covered.
- Dry Run: s = "010", x = 0
  i=1 ('1'): diff[1]++, diff[2]--
  Prefix sums: 
  index 0: 0 (Uncovered!) -> Return false.
- Time Complexity: O(N) - single pass to mark boundaries, single pass to check.
- Space Complexity: O(N) for the difference array.
- Why better than previous: Solves the overlapping iterations issue, bringing TC strictly to O(N).
- When to use: When range updates are required and array transformations are necessary.

======================================================================================
3. Optimal Approach (Gap Counting / Previous Position Tracking)
======================================================================================
- Intuition: We do not need extra space. We only care about the gaps between consecutive 
  WiFi routers and the un-covered edges (start to first router, last router to end).
- Approach: Maintain the index of the `lastWifi` seen. 
  1. If it's the first router seen, its distance from index 0 must be <= x.
  2. For subsequent routers, the gap between it and `lastWifi` must be <= 2*x 
     (since `lastWifi` covers x to the right, and the current covers x to the left).
  3. After iterating, check if the distance from the last router to the end of the 
     string is <= x. If any condition fails, return false.
- Dry Run: s = "10010", x = 1
  i=0: first router. 0 <= 1 (Valid). `lastWifi` = 0.
  i=3: next router. gap = 3 - 0 - 1 = 2. 2 <= 2*1 (Valid). `lastWifi` = 3.
  End of string check: (5 - 1) - 3 = 1. 1 <= 1 (Valid). All true.
- Time Complexity: O(N) - single pass.
- Space Complexity: O(1) - purely variable based.
- Why better than previous: Entirely eliminates the O(N) auxiliary space usage.
- When to use: Standard environments, CP, and Interviews (highly recommended).

Comparison Table:
Method               | TC       | SC    | Best Use Case
--------------------------------------------------------------------------------------
Brute Force          | O(N*X)   | O(N)  | Very basic debugging
Line Sweep           | O(N)     | O(N)  | When multiple different ranges update an array
Gap Counting         | O(N)     | O(1)  | Competitive Programming & Optimal Solution

Final Recommended Solution: Method 3 (Gap Counting / O(1) Space Approach)
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool wifiRange(string &s, int x) {
        int n = s.length();
        int lastWifi = -1;
        
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                if (lastWifi == -1) {
                    // Check if the first wifi router reaches the 0-th room
                    if (i > x) {
                        return false;
                    }
                } else {
                    // Check if the gap between the last router and current router is covered
                    // Gap formula between two indices (i, j): i - j - 1
                    int gap = i - lastWifi - 1;
                    if (gap > 2 * x) {
                        return false;
                    }
                }
                lastWifi = i;
            }
        }
        
        // Edge case: No wifi router exists in the entire hostel
        if (lastWifi == -1) {
            return false;
        }
        
        // Check if the last wifi router reaches the final room (n - 1)
        if ((n - 1) - lastWifi > x) {
            return false;
        }
        
        return true;
    }
};

// =====================================================================
// Driver Code to test the approach locally (Not required on GFG portal)
// =====================================================================
/*
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, x;
        string s;
        // Standard GFG local test format: N X then S
        cin >> n >> x; 
        cin >> s;
        
        Solution obj;
        if(obj.wifiRange(s, x)) cout << "1\n";
        else cout << "0\n";
    }
    return 0;
}
*/
