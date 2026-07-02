#include "LucidDream.h"
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

LucidDream::LucidDream() : Dream(), root(nullptr) { }
LucidDream::LucidDream(const string& dreamerName) : Dream(dreamerName), root(nullptr) { }

LucidDream::~LucidDream() {
    deleteTree(root);
}

void LucidDream::deleteTree(TreeNode* node) {
    if (!node) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void LucidDream::loadScenesFromFile(const string& filePath) {
    ifstream file;
    file.open(filePath);

    if (file.fail()) {
        cerr << "Could not open file at " << filePath << endl;
        return;
    }

    int numScenes;

    if (!(file >> numScenes)) {
        cerr << "Invalid input file. Missing information." << endl;
        exit(1);
    }

    file.ignore(); // Ignore the newline


    if (numScenes <= 0) {
        cerr << "Invalid input file. Number of scenes must be greater than 0." << endl;
        exit(1);
    }


    scenes.clear(); // Ensure the vector is empty before populating
    string shortDesc, longDesc;

    for (int i = 0; i < numScenes; i++) {
        getline(file, shortDesc);
        getline(file, longDesc);
        file.ignore(); // Ignore the newline

        scenes.emplace_back(shortDesc.substr(7), longDesc.substr(10)); // Remove "Short:" and "Detailed:"
    }

    file.close();

    root = buildTreeFromScenes();
}

LucidDream::TreeNode* LucidDream::buildTreeFromScenes() const {
    if (scenes.empty()) {
        return nullptr;
    }

    queue<TreeNode*> nodesQueue;
    TreeNode* rootNode = new TreeNode(scenes[0].first, scenes[0].second); // Use short and long descriptions
    nodesQueue.push(rootNode);

    int index = 1;

    while (index < scenes.size() && !nodesQueue.empty()) {
        TreeNode* currentNode = nodesQueue.front();
        nodesQueue.pop();

        if (index < scenes.size()) {
            currentNode->left = new TreeNode(scenes[index].first, scenes[index].second);
            nodesQueue.push(currentNode->left);
            index++;
        }

        if (index < scenes.size()) {
            currentNode->right = new TreeNode(scenes[index].first, scenes[index].second);
            nodesQueue.push(currentNode->right);
            index++;
        }
    }

    return rootNode;
}