void postOrder(Node *root)
{
    // If root is null, return (no more children)
    if (root == nullptr)
        return;

    // Recursively traverse left subtree
    postOrder(root->left);

    // Recursively traverse right subtree
    postOrder(root->right);

    // Print root
    cout << root->data << " ";
}

// Complexity: O(n)