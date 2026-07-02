#ifndef DREAM_GENERATOR_RECURSIVELUCIDDREAM_H
#define DREAM_GENERATOR_RECURSIVELUCIDDREAM_H

#include "../LucidDream.h"
#include <vector>
#include <string>

class RecursiveLucidDream : public LucidDream {
private:
    vector<int> escapePath;
    void traverseTree(TreeNode* node, int step) const;
    void generateEscapePath(TreeNode* node);
public:
    RecursiveLucidDream();
    RecursiveLucidDream(const string& dreamerName);

    void loadEscapePath(const vector<int>& path);
    void generateDream() const override;
};

#endif //DREAM_GENERATOR_RECURSIVELUCIDDREAM_H
