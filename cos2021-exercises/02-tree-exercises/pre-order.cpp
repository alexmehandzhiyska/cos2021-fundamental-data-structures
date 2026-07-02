void preOrder(Node *root)
{
    // If the root is null, return (no more children)
    if (root == nullptr)
        return;

    // First print the root (pre-order)
    cout << root->data << " ";

    // Recursively traverse left subtree
    preOrder(root->left);

    // Recursively traverse right subtree
    preOrder(root->right);
}

// Complexity: O(n)