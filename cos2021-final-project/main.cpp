#include <iostream>
#include <thread>
#include "./Dream/Nightmare/ChaseNightmare/ChaseNightmare.h"
#include "./Dream/Nightmare/ChaseNightmare/ChaseNightmare.cpp"
#include "./Dream/Nightmare/TrappedNightmare/TrappedNightmare.cpp"
#include "./Dream/Nightmare/Nightmare.cpp"
#include "./Dream/Dream.cpp"
#include "./Dream/LucidDream/LucidDream.cpp"
#include "./Dream/LucidDream/PeacefulLucidDream//PeacefulLucidDream.cpp"
#include "./Dream/LucidDream/RecursiveLucidDream/RecursiveLucidDream.cpp"

using namespace std;

int main() {
    cout << "As you drift off to sleep, a strange voice echoes in your mind.\n";
    this_thread::sleep_for(chrono::seconds(2));

    cout << "\nFirst, share your name, dreamer: " << endl;
    string name;
    cin >> name;

    cin.ignore(); // Ignore new line

    this_thread::sleep_for(chrono::seconds(2));
    cout << "\n" << name << ", tonight, your dreams will guide you... but the path is yours to choose.\n";

    this_thread::sleep_for(chrono::seconds(2));

    Dream* dream;

    while (true) {
        cout << "\nDo you wish to:\n";
        cout << "1. Outrun a relentless force in a perilous chase? (Chase Nightmare)\n";
        cout << "2. Find your way out of a sinister labyrinth, trapped with no clear escape? (Trapped Nightmare)\n";
        cout << "3. Explore a serene, boundless world where peace and beauty await? (Peaceful Lucid Dream)\n";
        cout << "4. Step into a recursive loop of dreams within dreams, testing the limits of your mind? (Recursive Lucid Dream)\n";

        string input;
        getline(cin, input);

        try {
            int choice = stoi(input);

            if (choice == 1) {
                dream = new ChaseNightmare(name);
                dream->loadScenesFromFile("./Dream/Nightmare/ChaseNightmare/scenes.txt");
                break;

            } else if (choice == 2) {
                dream = new TrappedNightmare(name);
                dream->loadScenesFromFile("./Dream/Nightmare/TrappedNightmare/scenes.txt");
                break;

            } else if (choice == 3) {
                dream = new PeacefulLucidDream(name);
                dream->loadScenesFromFile("./Dream/LucidDream/PeacefulLucidDream/scenes.txt");
                break;

            } else if (choice == 4) {
                dream = new RecursiveLucidDream(name);
                dream->loadScenesFromFile("./Dream/LucidDream/RecursiveLucidDream/scenes.txt");
                break;

            } else {
                cout << "\nInvalid input! Out of range number. Enter number between 1 and 4." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                continue;
            }
        } catch (const invalid_argument&) {
            cout << "\nInvalid input! The input should be a number." << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    dream->generateDream();
    return 0;
}