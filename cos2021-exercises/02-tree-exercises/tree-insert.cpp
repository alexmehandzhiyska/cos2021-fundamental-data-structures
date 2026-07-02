Node *insert(Node *root, int data)
{
    // If root is null, we've reached an empty spot in the tree where the new node should be inserted
    if (root == nullptr)
        return new Node(data);

    // If the new value is less than the root, we go to the left
    if (data < root->data)
        root->left = insert(root->left, data);
    // Else, we go to the right
    else
        root->right = insert(root->right, data);

    // Return the root after adding the new node.
    return root;
}

