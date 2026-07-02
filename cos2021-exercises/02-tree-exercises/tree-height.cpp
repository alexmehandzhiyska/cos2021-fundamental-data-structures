int height(Node *root)
{
    // If the root is null, the height is -1 (we're beyond a leaf node)
    if (root == nullptr)
        return -1;

    // Recursively call the height function on the left subtree
    int lh = height(root->left);

    // Recursively call the height function on the right subtree
    int rh = height(root->right);

    // Return max height + 1 to account for the current node.
    return max(lh, rh) + 1;
}

// Complexity : O(n)