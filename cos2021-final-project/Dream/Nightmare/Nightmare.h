#ifndef DREAM_GENERATOR_NIGHTMARE_H
#define DREAM_GENERATOR_NIGHTMARE_H

#include "../Dream.h"
#include <vector>
#include <string>

using namespace std;

class Nightmare : public Dream {
private:
    int generateDreamIntensity();

protected:
    int intensity;

public:
    Nightmare();
    Nightmare(const string& dreamerName);

    virtual ~Nightmare();
};

#endif //DREAM_GENERATOR_NIGHTMARE_H
