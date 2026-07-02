#ifndef DREAM_GENERATOR_PEACEFULLUCIDDREAM_H
#define DREAM_GENERATOR_PEACEFULLUCIDDREAM_H

#include "../LucidDream.h"

class PeacefulLucidDream : public LucidDream {
private:
    void traverseTree(TreeNode* node) const;

public:
    PeacefulLucidDream();
    PeacefulLucidDream(const string& dreamerName);

    void generateDream() const override;
};

#endif //DREAM_GENERATOR_PEACEFULLUCIDDREAM_H