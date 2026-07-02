node *insert(node *root, int val)
{
    if (!root)
    {
        // Create a new node if the tree is empty
        node *newNode = new node();
        newNode->val = val;
        newNode->left = newNode->right = nullptr;
        newNode->ht = 0; // Height of a new leaf is 0
        return newNode;
    }

    if (val < root->val)
    {
        root->left = insert(root->left, val); // Insert in the left subtree
    }
    else if (val > root->val)
    {
        root->right = insert(root->right, val); // Insert in the right subtree
    }
    else
    {
        return root; // Duplicate values are not allowed
    }

    // Update the height of the current node
    int leftHeight = root->left ? root->left->ht : -1;
    int rightHeight = root->right ? root->right->ht : -1;
    root->ht = 1 + std::max(leftHeight, rightHeight);

    // Calculate the balance factor
    int balance = leftHeight - rightHeight;

    // Balance the tree if needed
    // Left Left Case
    if (balance > 1 && val < root->left->val)
    {
        node *leftChild = root->left;
        root->left = leftChild->right;
        leftChild->right = root;

        // Update heights
        root->ht = 1 + std::max(
                           root->left ? root->left->ht : -1,
                           root->right ? root->right->ht : -1);
        leftChild->ht = 1 + std::max(
                                leftChild->left ? leftChild->left->ht : -1,
                                root->ht);

        return leftChild; // Return new root
    }

    // Right Right Case
    if (balance < -1 && val > root->right->val)
    {
        node *rightChild = root->right;
        root->right = rightChild->left;
        rightChild->left = root;

        // Update heights
        root->ht = 1 + std::max(
                           root->left ? root->left->ht : -1,
                           root->right ? root->right->ht : -1);
        rightChild->ht = 1 + std::max(
                                 root->ht,
                                 rightChild->right ? rightChild->right->ht : -1);

        return rightChild; // Return new root
    }

    // Left Right Case
    if (balance > 1 && val > root->left->val)
    {
        node *leftChild = root->left;
        node *leftRightChild = leftChild->right;

        leftChild->right = leftRightChild->left;
        leftRightChild->left = leftChild;
        root->left = leftRightChild->right;
        leftRightChild->right = root;

        // Update heights
        leftChild->ht = 1 + std::max(
                                leftChild->left ? leftChild->left->ht : -1,
                                leftChild->right ? leftChild->right->ht : -1);
        root->ht = 1 + std::max(
                           root->left ? root->left->ht : -1,
                           root->right ? root->right->ht : -1);
        leftRightChild->ht = 1 + std::max(
                                     leftChild->ht,
                                     root->ht);

        return leftRightChild; // Return new root
    }

    // Right Left Case
    if (balance < -1 && val < root->right->val)
    {
        node *rightChild = root->right;
        node *rightLeftChild = rightChild->left;

        rightChild->left = rightLeftChild->right;
        rightLeftChild->right = rightChild;
        root->right = rightLeftChild->left;
        rightLeftChild->left = root;

        // Update heights
        rightChild->ht = 1 + std::max(
                                 rightChild->left ? rightChild->left->ht : -1,
                                 rightChild->right ? rightChild->right->ht : -1);
        root->ht = 1 + std::max(
                           root->left ? root->left->ht : -1,
                           root->right ? root->right->ht : -1);
        rightLeftChild->ht = 1 + std::max(
                                     root->ht,
                                     rightChild->ht);

        return rightLeftChild; // Return new root
    }

    return root; // Return unchanged root if balanced
}