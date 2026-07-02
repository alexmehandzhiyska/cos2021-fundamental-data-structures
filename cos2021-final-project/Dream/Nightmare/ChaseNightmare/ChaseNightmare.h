#ifndef DREAM_GENERATOR_CHASENIGHTMARE_H
#define DREAM_GENERATOR_CHASENIGHTMARE_H

#include "../Nightmare.h"
#include <iostream>
#include <vector>

using namespace std;

class ChaseNightmare : public Nightmare {
private:
    struct Scene {
        string description;
        int weight;

        Scene(const string& description, int weight) : description(description), weight(weight) {}
    };

    vector<Scene> scenes;
    string entity;
    int proximity;
    int pursuerSpeed;

    int generatePursuerSpeed() const;
    string generateEntity() const;
    void updateProximity(const Scene& scene);
    string getProgressMessage() const;
    void concludeNightmare() const;

public:
    ChaseNightmare();
    ChaseNightmare(const string& dreamerName);

    void loadScenesFromFile(const string& filePath) override;
    void generateDream() const override;

    ~ChaseNightmare();
};

#endif //DREAM_GENERATOR_CHASENIGHTMARE_H
