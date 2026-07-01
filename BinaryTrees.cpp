/*
Binary Tree
- Maximum Depth (Basic DFS)
- Diameter of Binary Tree
- Maximum Path Sum
- Bottom View
- Left / Right View
- LCA in BT

- Maximum Width of BT
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

// Top View of BT
/* Given the root of a binary tree, return the top view of the binary tree.
Top view of a binary tree is the set of nodes visible when the tree is viewed from the top. Return nodes from the 
leftmost node to the rightmost node. Also if 2 nodes are outside the shadow of the tree and are at the same position 
then consider the left ones only(i.e. leftmost).  */

class Solution {
   public:
    vector<int> topView(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) return ans;
        map<int, int> mpp;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            TreeNode* node = it.first;
            int line = it.second;
            if (mpp.find(line) == mpp.end()) {
                mpp[line] = node->data;
            }
            if (node->left != nullptr) {
                q.push({node->left, line - 1});
            }
            if (node->right != nullptr) {
                q.push({node->right, line + 1});
            }
        }
        // mpp is sorted so it will take indexs -2 , -1, 0, 1, 2
        for (auto it : mpp) {
            ans.push_back(it.second);
        }
        return ans;
    }
};
// TC: O(N*logK) (N since each node visited exactly once * log K for map
// operations) SC: O(N) (extra space required by queue ds)

// LCA in BT (Lowest Common Ancestor) (Divide & Conquer)
/* Given a root of binary tree, find the lowest common ancestor (LCA) of two given nodes (p, q) in the tree.
The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has 
both p and q as descendants (where we allow a node to be a descendant of itself). */
class Solution {
   public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // base case
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        // Search in left and right subtrees
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        // result | Backtracking
        if (left == NULL) {
            return right;
        } else if (right == NULL) {
            return left;
        } else {
            return root;
        }
    }
};
// TC: O(N) | SC: O(N) (RSS)

// Right/Left View of BT
/* Assuming standing on the right side of a binary tree and given its root, return the values of the nodes visible, 
arranged from top to bottom. */
class Solution {
public:
    void recursionRight(TreeNode* root, int level, vector<int>& res){
        if(root == nullptr) return;
        if(res.size() == level){
            res.push_back(root->data);
        }
        recursionRight(root->right, level+1, res);
        recursionRight(root->left, level+1, res);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        recursionRight(root, 0, res);
        return res;
    }
};
// TC: O(N) (Each node is visited exactly once)
// SC: O(H) (Height of BT due to RSS)
/* In a balanced tree, height H is nearly equal to logN. Hence, the best-case space complexity is O(logN).
In a skewed tree, height H is almost equal to N. Hence, the worst-case space complexity turns out to be O(N). */

