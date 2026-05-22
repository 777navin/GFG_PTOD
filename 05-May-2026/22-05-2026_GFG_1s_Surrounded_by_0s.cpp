/*
Date: 22-05-2026
Problem Name: 1s Surrounded by 0s (Enclosed Islands variant)
Platform: GeeksforGeeks (GFG)
Difficulty: Medium
Tags: Matrix, Depth First Search (DFS), Breadth First Search (BFS), Graph

Problem Summary:
Given an n x m binary matrix grid[][], find the total count of all cells containing 1 
that are unable to move out of the grid through a path of adjacent 1s (Up, Down, Left, Right). 
Any 1 located on the boundary (first/last row or column) or connected to a boundary 1 can 
escape outside. We need to count the remaining '1's that are completely trapped by '0's.

Methods to Solve:
1. Optimal Approach (Boundary DFS / Flood Fill)

-----------------------------------------------------------------------------------------
Method 1: Optimal Approach (Boundary DFS / Flood Fill)
-----------------------------------------------------------------------------------------
- Intuition:
  Instead of finding which '1's are trapped, it is much easier to find which '1's can escape. 
  Any '1' on the boundary can escape. Any '1' connected to these boundary '1's can also escape. 
  If we traverse from all boundary '1's and mark them (and their connected components) as visited 
  (or turn them into '0's temporarily), the remaining '1's left in the grid are guaranteed to be 
  trapped.

- Approach:
  1. Traverse the outer boundaries of the grid (first row, last row, first column, last column).
  2. Whenever a '1' is found on the boundary, trigger a DFS/BFS to traverse all connected '1's.
  3. During the traversal, change the escaping '1's to a placeholder value (e.g., -1) to avoid re-visiting.
  4. After checking all boundaries, iterate through the entire matrix:
     - Count the remaining cells that still contain '1'.
     - (Optional) Restore the -1 cells back to '1' if the original grid modification needs to be undone.
  5. Return the total count of trapped '1's.

- Dry Run (Small Example):
  Grid:
  0 0 0 0
  1 0 1 0
  0 1 1 0
  0 0 0 0

  Step 1: Boundary check. 
  At grid[1][0], there is a '1'. Run DFS. It has no adjacent '1's. Convert grid[1][0] to -1.
  Grid becomes:
  0  0 0 0
 -1  0 1 0
  0  1 1 0
  0  0 0 0

  Step 2: Scan interior for remaining '1's.
  Cells grid[1][2], grid[2][1], and grid[2][2] are '1's and cannot reach the boundary.
  Count = 3.

- Time Complexity: O(n * m), where n is the number of rows and m is the number of columns. 
  Each cell is visited a constant number of times during the boundary scan and final counting phase.
- Space Complexity: O(n * m) in the worst case for the implicit recursive stack during DFS 
  (e.g., if the entire grid consists of escaping '1's).
- Why better than previous method: This avoids complex state tracking from interior cells by 
  leveraging the boundary conditions directly.
- When to use: Standard and most efficient pattern for boundary-connected grid problems.

Comparison Table:
Method           | TC        | SC        | Best Use Case
-----------------------------------------------------------------------------------------
Boundary DFS     | O(n * m)  | O(n * m)  | When grid dimensions are up to 500x500.

Final Recommended Solution:
Boundary DFS / Flood Fill method because it optimizes cell state transitions cleanly and operates 
within optimal time and space boundaries.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Direction vectors for moving Up, Down, Left, and Right
    const int delRow[4] = {-1, 1, 0, 0};
    const int delCol[4] = {0, 0, -1, 1};

    // Helper method to perform Depth First Search from boundary elements
    void dfs(int r, int c, vector<vector<int>>& grid, int n, int m) {
        // Mark the current cell as visited/escaped by changing its value
        grid[r][c] = -1;

        // Traverse all 4 adjacent directions
        for (int i = 0; i < 4; ++i) {
            int nRow = r + delRow[i];
            int nCol = c + delCol[i];

            // Check boundaries and see if the neighboring cell is an unvisited land cell '1'
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && grid[nRow][nCol] == 1) {
                dfs(nRow, nCol, grid, n, m);
            }
        }
    }

public:
    int cntOnes(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
        int m = grid[0].size();

        // Step 1: Traverse boundary columns for the first and last rows
        for (int j = 0; j < m; ++j) {
            // First Row
            if (grid[0][j] == 1) {
                dfs(0, j, grid, n, m);
            }
            // Last Row
            if (grid[n - 1][j] == 1) {
                dfs(n - 1, j, grid, n, m);
            }
        }

        // Step 2: Traverse boundary rows for the first and last columns
        for (int i = 0; i < n; ++i) {
            // First Column
            if (grid[i][0] == 1) {
                dfs(i, 0, grid, n, m);
            }
            // Last Column
            if (grid[i][m - 1] == 1) {
                dfs(i, m - 1, grid, n, m);
            }
        }

        // Step 3: Count the remaining trapped '1's and restore the grid state
        int trappedOnesCount = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    trappedOnesCount++;
                } else if (grid[i][j] == -1) {
                    grid[i][j] = 1; // Restoring original grid structure
                }
            }
        }

        return trappedOnesCount;
    }
};
