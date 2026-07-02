#include "ChaseNightmare.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <sstream>

using namespace std;

ChaseNightmare::ChaseNightmare() : Nightmare(), entity(generateEntity()), proximity(100), pursuerSpeed(generatePursuerSpeed()) { }
ChaseNightmare::ChaseNightmare(const string& dreamerName) : Nightmare(dreamerName), entity(generateEntity()), proximity(100), pursuerSpeed(generatePursuerSpeed()) { }

int ChaseNightmare::generatePursuerSpeed() const {
    srand(time(0));
    int speed = rand() % 10 + 1;
    return speed;
}

string ChaseNightmare::generateEntity() const {
    vector<string> entities;

    entities.push_back("monster");
    entities.push_back("snake");
    entities.push_back("Severus Snape");
    entities.push_back("dark shadow");

    srand(time(0));

    int randomIndex = rand() % entities.size();

    // Return randomly selected chasing entity
    return entities[randomIndex];
}

void ChaseNightmare::loadScenesFromFile(const string& filePath) {
    ifstream file;
    file.open(filePath);

    if (file.fail()) {
        cout << "Cannot open file at " << filePath << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream stream(line); // Turn the line into a stream to read the separate parts
        string description;
        int weight;

        // Get the description
        getline(stream, description, ';');

        // Add scene only if the description is not empty and if able to read the weight
        if (!description.empty() && stream >> weight) {
            scenes.emplace_back(description, weight);
        }
    }

    file.close();
}

void ChaseNightmare::updateProximity(const Scene& scene) {
    proximity -= pursuerSpeed * scene.weight * (intensity / 10.0); // Dynamically calculate the proximity

    string message = getProgressMessage();
    cout << message << "\n\n";
    this_thread::sleep_for(chrono::seconds(2));
}

void ChaseNightmare::concludeNightmare() const {
    // Generate random number to choose from 3 different sentences for the same type of ending
    srand(time(0));
    int endingType = rand() % 3;

    if (proximity <= 0) {
        cout << "\n⢯⠽⣙⢮⡝⣎⡳⡝⣎⢳⣙⢎⡳⣍⠞⣥⢛⡼⣡⢛⡬⢳⡍⢮⡱⣍⢮⡱⣍⠮⡱⡍⢮⡱⢍⢮⡱⢫⡜⣣⢛⣜⢣⡻⣜⢭⡳⣭⠯⡽⣭⢻⡽⣹⢏⣿⡹⣯⣟⢿⣻⢿\n"
                "⢯⡹⣍⠶⣙⠶⣩⢓⣎⢧⣙⢮⡱⢎⡝⢦⣋⠶⣱⢫⡜⣣⠞⡥⢳⡘⡆⠳⠈⠘⠓⠙⠀⠷⠍⣶⢉⡗⡼⣡⢏⡜⣣⠗⣎⢧⡝⣖⢯⢳⣭⠳⣝⢧⡻⣖⣻⢵⣫⢿⡽⣻\n"
                "⢧⡓⢮⣙⢎⡳⢥⢏⡜⢦⡙⣦⡙⣎⢞⡱⢎⡳⢥⠳⡜⣥⠚⠅⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠓⠥⣚⠼⣡⢛⡜⣎⢞⡼⢎⡗⣎⠿⣜⢧⡻⣜⡧⢿⣹⢾⣹⢷\n"
                "⢧⡙⢧⡚⣬⠳⣍⠞⣜⢣⡝⢦⡹⣜⢪⡕⣫⠜⣣⢏⠒⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢳⢥⢫⡜⢮⡝⡼⣍⠾⣩⢻⡜⣧⢻⡼⣹⢳⣏⢯⣳⢯\n"
                "⢧⡙⣦⡙⢦⡛⣬⢛⡬⠳⣜⢣⠳⣌⠳⣜⣡⢛⡴⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢪⠩⣖⡹⢦⡹⢖⡭⣋⠷⣣⢻⡜⣧⢻⡵⣫⠾⣭⣳⢯\n"
                "⢧⡙⢦⡙⣦⡙⢦⣋⠶⡹⣌⠧⣛⢬⠳⣜⢢⡓⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠱⡝⢦⡹⣚⠶⣩⠯⣕⢯⡺⣕⢯⣜⡳⣏⣷⡹⣞\n"
                "⢧⡙⣦⡙⢦⡙⢦⢣⠏⡵⢪⡕⣣⢎⡳⣌⠳⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡀⢛⡧⢳⡍⡾⣱⢫⢎⡗⢧⡻⣜⢮⡳⣝⢶⣫⢽\n"
                "⢧⡙⢦⡙⢦⡛⣬⢣⡛⡼⣑⢮⠱⣎⡱⣌⡇⠀⠀⠀⠀⠀⠀⢀⣀⣀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⣤⣀⠀⢠⣀⠀⣽⡆⠈⣭⡓⢮⡵⣙⢮⡝⣺⢣⡝⣮⢳⡝⣮⢷⣹⢞\n"
                "⡎⡝⢦⡹⢲⡙⢦⢣⢳⡱⡍⢶⡹⡰⢃⢮⠀⠀⠀⠀⠀⣰⣾⣿⣿⣿⣿⣦⡀⠀⠀⢀⣱⣿⣿⣿⣿⣿⣷⡀⠹⣶⡥⡇⠀⢰⡝⣣⠞⣭⠶⣹⢥⡻⣜⢧⡻⣜⢧⡻⣜⢯\n"
                "⢧⡙⢦⣙⢣⡝⢎⡣⢇⡳⣍⠶⣱⣉⠏⣾⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⡇⠀⠀⠸⣿⣿⣿⠟⠙⢿⣿⣷⡀⠸⣿⡅⠀⠀⡟⡴⣛⣬⠳⣭⠶⣙⠾⡜⣧⣛⢮⡳⣽⢺\n"
                "⢧⡙⢦⡙⢦⡙⢮⡱⢋⠶⡱⣚⢤⣓⢚⡼⠀⠀⠀⠀⠀⣿⣿⣿⠉⠙⣿⣿⡟⠀⣀⣀⢿⣿⣿⣦⣤⣼⣿⣿⠃⠀⣹⢣⠀⠀⠸⡵⢣⡞⣹⣒⠯⣭⠯⣝⢶⡹⣎⠷⣭⢻\n"
                "⢧⡙⢦⡹⢲⡙⢦⡹⢍⡞⣥⢓⠮⡔⣫⠀⠈⡤⠀⠀⠀⠿⣿⣿⣦⣴⣿⡿⠁⢰⣿⣿⡌⣿⠻⠿⣿⣿⠟⠁⠀⠀⣯⠟⡄⠀⠠⢟⢧⡹⢵⣊⠿⡴⣛⡼⣣⢟⡼⣻⡜⣯\n"
                "⢧⡙⢦⡙⢧⡙⢦⡙⠎⠀⠈⣣⢝⡲⠹⠀⠀⢡⠀⠀⠀⠀⠈⣙⡟⢻⡏⠀⠀⢾⠇⣿⠷⢹⣧⠀⠀⢀⠀⠀⠀⠀⡞⠽⢷⠀⠀⢸⡧⣛⣬⢳⢫⡵⢫⢶⡹⣎⢷⣣⢟⡼\n"
                "⢧⡙⢦⡝⢦⡹⢲⣍⢻⠀⠀⢛⢦⡱⡇⠀⠘⠸⠀⠀⠀⠀⢰⡏⠃⣼⡄⠀⣀⢀⣀⣈⣤⠛⠋⠀⠀⣼⠀⠀⠀⠀⠇⠀⠘⣆⠀⠈⢳⣭⢲⣋⢷⠺⣝⢮⡳⣝⢮⡳⣏⢾\n"
                "⣣⠝⣦⡙⢦⡙⢧⣌⠳⡄⠀⠙⣇⠞⡇⠀⠀⢱⡆⡀⠀⠀⠀⠀⠄⢻⣯⣼⠿⡟⢻⡛⢟⢿⣷⣤⣽⣿⣇⠀⠀⠀⢽⠀⠀⡿⡄⠀⠄⢣⢷⣙⢮⡻⣜⢧⡻⣜⢧⡻⣜⢯\n"
                "⣇⢻⡰⣙⢮⡙⠶⣌⠳⠇⠀⠀⣾⢫⠁⠀⠀⢱⣄⠀⠀⠀⠀⠀⠀⠀⣿⣏⣶⣷⣾⣷⣿⣥⢻⣿⣧⣿⣿⠎⠀⠀⣾⠀⠀⡿⣱⠀⠀⠘⣧⢏⡾⣱⢏⡾⣱⢏⡾⣵⣛⢾\n"
                "⢎⢧⡓⣭⠲⣭⠳⡜⣭⢳⠀⠀⠸⣏⡀⠀⠀⢻⡽⠀⠀⠀⠀⠀⠀⢲⣿⣿⣿⣿⣿⣿⣿⣿⢻⣿⣿⡏⠏⣿⠀⢸⣿⠀⠀⢸⣳⢃⠀⠀⢹⣎⢷⡣⣟⡼⣣⢟⡼⣣⢟⣞\n"
                "⡏⢶⠹⣔⢫⢖⡹⡜⢦⡛⠀⠀⢰⣷⠃⠀⠀⠸⢳⠀⠐⠀⠀⠀⠈⣇⢿⣯⠻⡟⢿⠛⡯⢃⣿⣿⣿⠁⢠⡏⢰⣿⣿⠀⠐⢠⣭⣛⡀⠀⠀⢿⣎⠷⣭⢖⡯⣞⡽⣣⡟⡾\n"
                "⡝⣎⠳⣬⢓⢮⡱⣹⠲⣍⠇⠀⠀⢩⡇⠀⠀⢆⡷⠆⠀⠀⡆⠀⠀⢁⠸⠛⣍⡦⣼⠰⢰⣷⣿⡿⢉⠀⡸⢀⡿⢯⢽⠀⠀⢺⠶⣭⣃⠀⠀⠘⣯⡻⣜⢯⡞⣵⢫⢷⡹⣽\n"
                "⡽⣌⡳⢥⡛⢦⠳⣥⢛⡼⠀⠀⠀⠉⠀⠀⠀⠀⠉⠀⠀⠐⡇⠀⠀⠘⠀⠀⠘⣿⣿⢻⣿⣿⠟⠁⠀⢀⢣⣾⣙⢮⢳⠀⠀⢸⡝⡶⣭⡄⠀⠀⢻⣷⡹⣮⣝⢮⣛⣮⢽⣺\n"
                "⠷⣌⡳⢣⣝⢣⠟⡴⢫⣜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡄⠀⠀⠀⠀⠤⢏⡛⠇⠟⠁⣀⠀⢠⡾⣿⡱⣎⣏⡞⠀⠀⠸⣏⡷⣳⣤⠀⠀⠘⢷⣻⢶⡹⣞⣳⢮⣳⢽\n"
                "⡻⣔⢫⡳⡬⢏⡾⣩⢗⡺⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠁⠂⢀⠀⠀⠀⠈⠀⡸⠀⣠⢽⣵⢿⡽⣿⣿⣿⣶⣿⠀⠀⠀⠻⡾⠵⠊⠀⠀⠀⠀⠙⣾⡝⣧⡻⣞⡽⣺\n"
                "⢷⡩⢷⡱⣫⢳⠵⣋⢮⡵⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠈⠒⣒⡡⢴⡶⣜⢮⡻⣝⡾⣽⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢽⣿⣳⡽⣞⡵⣯\n"
                "⡳⣝⣣⠷⣩⠗⣯⠹⠞⠚⠣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡘⠀⠀⠀⠉⠒⠶⣭⡷⣾⣽⢾⡽⣯⢿⣻⡿⢯⡿⣛⠾⣥⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣷⣿⡻⣽⣛⣾\n"
                "⣝⢮⡵⠋⠉⠀⠀⠀⠀⠀⠀⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠁⠀⠀⠐⠤⢮⣙⡶⣹⠾⡽⣯⣻⡽⣟⠭⣹⡏⠱⡉⠞⠠⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣾⢿⣽\n"
                "⣏⣾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡇⠀⠀⠀⠀⠀⢢⢍⡳⡛⣟⠻⣍⠳⢉⠂⡃⠓⠀⠁⠀⠀⠀⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿\n"
                "⡷⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⢀⡟⠀⠀⠀⠀⣀⢎⡱⢊⠴⡑⠠⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿\n"
                "⡇⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⠀⠀⠀⢀⠴⣘⢦⠣⡍⠂⠄⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣹⣿⣿⣿⣿⣿\n"
                "⠁⠀⠀⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⠀⠀⠀⢰⣏⠃⠀⢀⠴⣋⠾⣍⢖⠣⠌⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⡰⡋⠽⣿⣿⣿⣿\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣽⡎⠀⣠⢞⡽⣝⡻⣜⢊⠱⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⢡⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠆⠀⠀⠀⠀⠀⠀⠀⢸⣷⠀⣧⣳⢯⡿⣭⠳⡜⢈⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡧⢀⣰⡀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿\n";

        switch (endingType) {
            case 0:
                cout << "\nThe " << entity << " catches you, and everything fades to black. You wake up in terror." << endl;
                break;

            case 1:
                cout << "\nThe " << entity << " corners you. Just as it strikes, you wake up gasping for air." << endl;
                break;

            case 2:
                cout << "\nYou feel the  " << entity << "'s icy grip as you wake up trembling in fear." << endl;
                break;
        }
    } else {
        cout << "\n"
                "⠀⠀⠀⠀⡔⠑⡄⣀⠤⠛⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠒⠢⢄⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⣠⠞⠀⠀⠸⡅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠢⡀⠀⠀⠀⠀\n"
                "⠀⡠⠃⠀⠀⠀⠀⠙⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠢⡀⠀ \n"
                "⢠⡇⠀⠀⠀⠀⠀⠀⢹⠤⠖⠒⠒⠤⡀⠀⠀⠀⢀⠠⠒⠉⠉⠑⠲⢄⠀⠘⢄⠀\n"
                "⡎⡇⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⣀⣈⢣⠀⢀⠆⠀⠀⠀⠀⣀⣤⣬⣣⠀⠈⡆\n"
                "⠇⠱⡀⠀⠀⠀⠀⢀⡜⠀⠀⠀⣾⣿⣿⣿⡇⢸⠀⠀⠀⠀⠰⣿⣿⣿⣿⠀⠀⢰\n"
                "⡇⠀⠉⠒⠢⠤⠶⡏⠀⠀⠀⠀⠙⠿⠿⢻⠇⠈⠄⠀⠀⠀⠀⠙⠛⠛⡹⠀⠀⢸\n"
                "⡇⠀⠀⠀⠀⠀⠀⠈⠢⢄⡀⠀⠀⣀⠔⠁⠀⠀⠈⠓⠤⣀⣀⡠⠤⠊⠀⠀⠀⢸\n"
                "⡇⠀⠀⠀⠀⠀⠀⠀⢀⣀⡈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⢸\n"
                "⠇⠀⠀⠀⠀⠀⠀⢰⣿⣿⠿⠿⠿⣷⣶⣶⣶⣶⣶⣶⡿⠿⠿⢿⣿⣷⠀⠀⠀⢸\n"
                "⠘⡄⠀⠀⠀⠀⠀⠀⢿⣿⣷⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣿⣿⠏⠀⠀⢠⠃\n"
                "⠀⠘⢄⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⣷⣶⣶⣶⣶⣿⣿⣿⣿⣿⠋⠀⠀⢠⠋⠀\n"
                "⠀⠀⠈⠢⡀⠀⠀⠀⠀⠀⠈⠛⠿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠋⠀⠀⢀⠔⠁⠀⠀\n"
                "⠀⠀⠀⠀⠈⠠⢀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠁⠀⠀⠀⣠⠔⠁⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠉⠒⠤⢄⣀⣀⣀⣀⣀⣀⣀⣀⣀⢤⠖⠏⠁⠀⠀⠀⠀⠀⠀\n";

        switch (endingType) {
            case 0:
                cout << "\nYou burst into the light and wake up, " << dreamerName << ", relieved that you didn't get caught." << endl;
                break;

            case 1:
                cout << "\nYou escape, " << dreamerName << ", but the " << entity << " still lingers in your thoughts." << endl;
                break;

            case 2:
                cout << "\nYou survive, " << dreamerName << ", but the  " << entity << "'s shadow haunts still haunts you." << endl;
                break;
        }
    }
}

string ChaseNightmare::getProgressMessage() const {
    vector<string> farMessages;
    farMessages.push_back("The " + entity + " is far behind, but it's closing in...");
    farMessages.push_back("You hear distant sounds of the " + entity + ", but it's still far away.");
    farMessages.push_back("The " + entity + " is somewhere in the distance. You have a chance to run faster.");

    vector<string> closeMessages;
    closeMessages.push_back("The " + entity + " is getting closer! You feel its presence behind you...");
    closeMessages.push_back("You can almost hear the " + entity + "'s footsteps. It's closing in...");
    closeMessages.push_back("The " + entity + " is creeping closer. You start to panic!");

    vector<string> veryCloseMessages;
    veryCloseMessages.push_back("The " + entity + " is right on your heels! You're running out of time...");
    veryCloseMessages.push_back("The " + entity + " is about to grab you! You sprint as fast as you can!");
    veryCloseMessages.push_back("The " + entity + " is breathing down your neck. You're desperate to escape!");

    // Use a differently scary type of message depending on how close the chaser is
    if (proximity > 50) {
        return farMessages[rand() % farMessages.size()];
    } else if (proximity > 20) {
        return closeMessages[rand() % closeMessages.size()];
    } else {
        return veryCloseMessages[rand() % veryCloseMessages.size()];
    }
}

void ChaseNightmare::generateDream() const {
    cout << "\n" << dreamerName << ", you peacefully fall asleep, but a nightmare begins..." << "\n\n";
    this_thread::sleep_for(chrono::seconds(2));


    for (const Scene& scene : scenes) {
        cout << scene.description << endl;
        this_thread::sleep_for(chrono::seconds(4));

        // Proximity gets changed dynamically
        const_cast<ChaseNightmare*>(this)->updateProximity(scene);

        if (proximity <= 0) {
            break;
        }
    }

    concludeNightmare();
}

ChaseNightmare::~ChaseNightmare() { }