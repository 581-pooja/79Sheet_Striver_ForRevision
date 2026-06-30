/*
Binary Tree
- Maximum Depth (Basic DFS)
- Diameter of Binary Tree
- Maximum Path Sum
- Bottom View
- LCA in BT
- Burning Tree
- Construct Tree from Preorder + Inorder
- Morris Preorder
BST
- Delete Node in BST
- LCA in BST
- Two Sum in BST
- Largest BST in Binary Tree
*/
// Maximum Depth in BT
/* Given root of the binary tree, return its maximum depth.
A binary tree's maximum depth is number of nodes along the longest path from from root node down to the farthest node. */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int lh = maxDepth(root->left);
        int rh = maxDepth(root->right);
        return 1 + max(lh, rh);
    }
};
// TC: O(N) (since visiting every node once)
// SC: O(N) (Stack space required by recursion)

// Iterative : Level order traversal (disadvantage using queue DS can take worst case O(N))
class Solution {
   public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            level++;
        }
        return level;
    }
};
// TC: O(N) (since visiting every node once)
// SC: O(N) (Stack space required by recursion)

// Diameter of Binary Tree
/* Given the root of a binary tree, return the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes 
in the tree. It may or may not pass through the root. */
class Solution {
public:
    int height(TreeNode* node, int& diameter){
        if(!node) return 0;
        int lh = height(node->left, diameter);
        int rh = height(node->right, diameter);
        diameter = max(diameter, lh + rh);
        return 1 + max(lh, rh);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        height(root, diameter);
        return diameter;
    }
};
// TC: O(N) (since every node is visited extactly once)
// SC: O(N) (auxillary stack space to store node calls or Height of Tree)

// Maximum path sum 
/* In a binary tree, a path is a list of nodes where there is an edge between every pair of neighbouring nodes. 
A node may only make a single appearance in the sequence. The total of each node's values along a path is its path sum. 
Return the largest path sum of all non-empty paths given the root of a binary tree. */

class Solution {	
public:
    int findMaxPathSum(TreeNode* root, int& maxi){
        if(root == nullptr){
            return 0;
        }
        int leftMaxPath = max(0, findMaxPathSum(root -> left, maxi));
        int rightMaxPath = max(0, findMaxPathSum(root -> right, maxi));
        maxi = max(maxi, leftMaxPath + rightMaxPath + root -> data);
        return root -> data + max(leftMaxPath, rightMaxPath);
    }
    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN;
        findMaxPathSum(root, maxi);
        return maxi;
    }
};	
// TC: O(N) | SC: O(H) (Recursive Stack Auxilliary space)