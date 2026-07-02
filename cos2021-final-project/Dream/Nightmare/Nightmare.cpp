#include "Nightmare.h"

using namespace std;

Nightmare::Nightmare() : Dream(), intensity(generateDreamIntensity()) { }
Nightmare::Nightmare(const string& dreamerName) : Dream(dreamerName), intensity(generateDreamIntensity()) { }

int Nightmare::generateDreamIntensity() {
    srand(time(0));

    // Generate intensity between 1 and 10
    int dreamIntensity = 1 + rand() % 10;
    return dreamIntensity;
}

Nightmare::~Nightmare() { }