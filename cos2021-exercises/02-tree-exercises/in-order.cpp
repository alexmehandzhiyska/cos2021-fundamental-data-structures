void inOrder(Node *root)
{
    // If root is null, return
    if (root == nullptr)
        return;

    // Recursively traverse left subtree
    inOrder(root->left);

    // Print root
    cout << root->data << " ";

    // Recursively traverse right subtree
    inOrder(root->right);
}

// Complexity: O(n)