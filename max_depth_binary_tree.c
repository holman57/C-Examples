int max(int a, int b) {
    return a>b?a:b;
}

int maxDepth(struct TreeNode* root) {
    
    if (root==NULL) {
        return 0;
    }    
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}