#include "RecursiveLucidDream.h"
#include <iostream>

using namespace std;

RecursiveLucidDream::RecursiveLucidDream() : LucidDream() { }
RecursiveLucidDream::RecursiveLucidDream(const string& dreamerName) : LucidDream(dreamerName) { }

void RecursiveLucidDream::generateEscapePath(TreeNode *node) {
    escapePath.clear();
    TreeNode* current = node;

    srand(time(0));

    // Randomly generate the correct escape path

    while (current) {
        if (!current->left && !current->right) {
            break;
        }

        // Choose direction - 1 for left, 2 for right
        int direction = (rand() % 2) + 1;
        escapePath.push_back(direction);

        if (direction == 1 && current->left) {
            current = current->left;
        } else if (direction == 2 && current->right) {
            current = current->right;
        } else {
            break;
        }
    }
}

void RecursiveLucidDream::traverseTree(TreeNode* node, int step) const {
    if (!node) {
        return;
    }

    this_thread::sleep_for(chrono::seconds(2));

    // Check if the current node is a leaf
    if (!node->left && !node->right) {
        if (step == escapePath.size()) {
            cout << "\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣴⣿⣿⣿⣿⣦⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⠿⠛⠛⠿⢿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⠏⢀⣴⣶⣶⣦⡄⠹⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⠀⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣦⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⢨⣿⣿⣿⡀⠻⣿⣿⣿⣿⠟⢀⣿⣿⣿⡅⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠈⠙⣿⣿⣿⣦⣄⣉⣉⣀⣴⣿⣿⣿⠋⠁⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⣿⣿⣿⣿⣿⣿⣿⣿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣉⡉⠻⠛⠛⠟⢉⣉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣦⡆⢰⣴⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⡇⢸⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⡇⢸⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡿⠃⠘⢿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡿⠋⠀⠀⠀⠀⠙⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
            cout << "\nYou step into the light, following the correct path. Good job! \n";
        } else {
            cout << "\nThis path leads to a dead end. You feel yourself pulled back to retry...\n";
        }

        return; // Stop recursion
    }

    int choice;

    while (true) {
        cout << "\nChoose your path:\n";

        if (node->left) {
            cout << "1. " << node->left->shortDescription << endl;
        }

        if (node->right) {
            cout << "2. " << node->right->shortDescription << endl;
        }

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n" << node->left->longDescription << endl;
        } else {
            cout << "\n" << node->right->longDescription << endl;
        }

        if (step < escapePath.size() && choice == escapePath[step]) {
            if (choice == 1 && node->left) {
                traverseTree(node->left, step + 1);
                return;
            } else if (choice == 2 && node->right) {
                traverseTree(node->right, step + 1);
                return;
            }
        } else {
            this_thread::sleep_for(chrono::seconds(2));
            cout << "You feel disoriented and must rethink your decision...\n";
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}

void RecursiveLucidDream::generateDream() const {
    cout << "\n" << dreamerName << ", you find yourself in a recursive lucid dream...\n";
    this_thread::sleep_for(chrono::seconds(2));

    if (!root) {
        cout << "The dream fades before it even begins...\n";
        return;
    }

    const_cast<RecursiveLucidDream*>(this)->generateEscapePath(root);
    traverseTree(root, 0);
}