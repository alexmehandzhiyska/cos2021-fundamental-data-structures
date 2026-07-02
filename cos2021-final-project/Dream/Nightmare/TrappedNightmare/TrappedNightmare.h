#ifndef DREAM_GENERATOR_TRAPPEDNIGHTMARE_H
#define DREAM_GENERATOR_TRAPPEDNIGHTMARE_H

#include "../Nightmare.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <stack>
#include <queue>

class TrappedNightmare : public Nightmare {
private:
    int duration;

    struct Scene {
        string description;
        vector<pair<int, int> > transitions;
    };

    vector<Scene> tree;
    mutable int timeRemaining;

    int generateDreamDuration();
    vector<int> findDijkstraPath(bool maximize) const;
    void traversePath(const vector<int>& path) const;

public:
    TrappedNightmare();
    TrappedNightmare(const string& dreamerName);

    void loadScenesFromFile(const string& filePath) override;
    void generateDream() const override;

    ~TrappedNightmare();
};

#endif //DREAM_GENERATOR_TRAPPEDNIGHTMARE_H
