/*
============================================================
  Date         : 23-05-2025
  Problem Name : Transform to Sum Tree
  Platform     : GeeksforGeeks (GFG)
  Difficulty   : Medium
  Tags         : Binary Tree, Tree Traversal, Postorder, Recursion
============================================================

  Problem Summary:
  ----------------
  Given a Binary Tree, transform it into a Sum Tree where every
  node's value is replaced by the sum of all values in its
  left and right subtrees (based on the ORIGINAL values).
  The leaf nodes become 0 (no children → sum = 0).

============================================================
  Methods to Solve:
============================================================

  ---------------------------------------------------------------
  METHOD 1 — BRUTE FORCE
  ---------------------------------------------------------------
  Intuition:
    For each node, traverse its entire left and right subtree
    separately to compute the sum, then assign it to the node.

  Approach:
    - Write a helper sumOfTree(node) that returns sum of all
      nodes in a subtree.
    - For every node (preorder), call sumOfTree(left) +
      sumOfTree(right) and assign to node->data.
    - Recurse for left and right children.

  Dry Run:
         1
        / \
       2   3
      / \
     4   5

    Node 1 → sumOfTree(left=2's subtree)=11, sumOfTree(right=3)=3 → data=14
    Node 2 → sumOfTree(left=4)=4, sumOfTree(right=5)=5 → data=9
    Node 4 → no children → data=0
    Node 5 → no children → data=0
    Node 3 → no children → data=0

    Result:
         14
        /  \
       9    0
      / \
     0   0

  Time Complexity  : O(n²) — for each node, full subtree traversal
  Space Complexity : O(h)  — recursion stack (h = height)

  When to Use: Only for very small trees / interview explanation.

  ---------------------------------------------------------------
  METHOD 2 — OPTIMAL (Single Postorder Traversal)
  ---------------------------------------------------------------
  Intuition:
    In postorder (Left → Right → Root), by the time we process
    a node, both its children are already processed. So we can
    capture original subtree sums on the way UP the recursion.

  Approach:
    - Define transform(node) that returns the ORIGINAL subtree
      sum rooted at node.
    - Save originalVal = node->data.
    - Recursively get leftSum  = transform(node->left)
                      rightSum = transform(node->right)
    - Update node->data = leftSum + rightSum
    - Return originalVal + leftSum + rightSum
      (so the parent gets the correct original sum)

  Dry Run:
         1
        / \
       2   3
      / \
     4   5

    transform(4): orig=4, L=0, R=0 → data=0,  return 4
    transform(5): orig=5, L=0, R=0 → data=0,  return 5
    transform(2): orig=2, L=4, R=5 → data=9,  return 11
    transform(3): orig=3, L=0, R=0 → data=0,  return 3
    transform(1): orig=1, L=11,R=3 → data=14, return 15

    Final Tree:
         14
        /  \
       9    0
      / \
     0   0  ✅

  Time Complexity  : O(n) — each node visited exactly once
  Space Complexity : O(h) — recursion stack
  Why Better       : Single pass vs O(n²) brute force
  When to Use      : Always — this is the standard optimal solution

============================================================
  Comparison Table:
  ---------------------------------------------------------
  Method          | TC     | SC   | Best Use Case
  ----------------|--------|------|------------------------
  Brute Force     | O(n²)  | O(h) | Explanation only
  Optimal (Post)  | O(n)   | O(h) | Always — interviews/prod
  ---------------------------------------------------------

  ✅ Final Recommended: METHOD 2 — Optimal Postorder Traversal
============================================================
*/

// ============================================================
//  GFG Driver-Compatible Solution (Do NOT redefine Node)
// ============================================================

class Solution {
public:

    // -------------------------------------------------------
    // METHOD 1 — Brute Force: O(n²)
    // -------------------------------------------------------

    // Helper: returns sum of all nodes in subtree
    int sumOfTree(Node* node) {
        if (node == nullptr)
            return 0;
        return node->data + sumOfTree(node->left) + sumOfTree(node->right);
    }

    void toSumTreeBrute(Node* node) {
        if (node == nullptr)
            return;

        // Store original value before overwriting
        int leftSum  = sumOfTree(node->left);
        int rightSum = sumOfTree(node->right);

        // Update current node
        node->data = leftSum + rightSum;

        // Recurse — NOTE: subtree sums already computed above
        // so children's originals are intact at this point
        toSumTreeBrute(node->left);
        toSumTreeBrute(node->right);
    }

    // -------------------------------------------------------
    // METHOD 2 — Optimal: Single Postorder Pass — O(n)
    // -------------------------------------------------------

    // Returns the ORIGINAL subtree sum rooted at 'node'
    int transform(Node* node) {
        // Base case: null node contributes 0
        if (node == nullptr)
            return 0;

        int originalVal = node->data;           // save before overwrite

        int leftSum  = transform(node->left);   // original left subtree sum
        int rightSum = transform(node->right);  // original right subtree sum

        // New value = sum of left + right subtrees (original values)
        node->data = leftSum + rightSum;

        // Return original value of this whole subtree to parent
        return originalVal + leftSum + rightSum;
    }

    // -------------------------------------------------------
    // GFG expected function — uses Optimal approach
    // -------------------------------------------------------
    void toSumTree(Node* node) {
        transform(node);
    }
};
