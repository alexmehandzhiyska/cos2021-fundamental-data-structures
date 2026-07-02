#ifndef DREAM_GENERATOR_LUCIDDREAM_H
#define DREAM_GENERATOR_LUCIDDREAM_H

#include "../Dream.h"
#include <vector>
#include <string>

using namespace std;

class LucidDream : public Dream {
protected:
    vector<pair<string, string> > scenes;

    struct TreeNode {
        string shortDescription;
        string longDescription;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const string& shortDescription, const string& longDescription) : shortDescription(shortDescription), longDescription(longDescription), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;
    TreeNode* buildTreeFromScenes() const;
    void deleteTree(TreeNode* node);

public:
    LucidDream();
    LucidDream(const string& dreamerName);
    virtual ~LucidDream();

    void loadScenesFromFile(const string& filePath) override;
    virtual void generateDream() const = 0;
};


#endif //DREAM_GENERATOR_LUCIDDREAM_H
