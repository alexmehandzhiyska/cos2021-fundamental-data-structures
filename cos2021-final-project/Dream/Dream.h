#ifndef DREAM_GENERATOR_DREAM_H
#define DREAM_GENERATOR_DREAM_H

#include <string>

using namespace std;

class Dream {
protected:
    string dreamerName;

public:
    Dream();
    Dream(const string& dreamerName);

    virtual void generateDream() const = 0;
    virtual void loadScenesFromFile(const string& filePath) = 0;

    virtual ~Dream();
};

#endif //DREAM_GENERATOR_DREAM_H
