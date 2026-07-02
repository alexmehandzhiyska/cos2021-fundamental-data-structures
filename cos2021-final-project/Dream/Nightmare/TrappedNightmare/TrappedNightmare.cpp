#include "TrappedNightmare.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <queue>

TrappedNightmare::TrappedNightmare() : Nightmare() {
    duration = generateDreamDuration();
    timeRemaining = duration;
}
TrappedNightmare::TrappedNightmare(const string& dreamerName) : Nightmare(dreamerName) {
    duration = generateDreamDuration();
    timeRemaining = duration;
}

int TrappedNightmare::generateDreamDuration() {
    srand(time(0));

    const int minDuration = 30;
    const int maxDuration = 300;
    const int minIntensity = 1;
    const int maxIntensity = 10;

    // Sub-range width ensures distinct durations per intensity
    const int subRangeWidth = 20;

    // Calculate duration that's within the boundaries but also based on intensity
    int baseDuration = minDuration + (int)(maxDuration - minDuration) * (maxIntensity - intensity) / (maxIntensity - minIntensity);

    // Add a small random variation within the sub-range
    int dur = baseDuration + rand() % subRangeWidth;

    // Ensure the duration stays within bounds
    dur = max(minDuration, min(maxDuration, dur));

    return dur;
}

void TrappedNightmare::loadScenesFromFile(const string& filePath) {
    ifstream file;
    file.open(filePath);

    if (file.fail()) {
        cout << "Could not open file at " << filePath << endl;
        return;
    }

    int numScenes;
    file >> numScenes;
    tree.resize(numScenes);

    file.ignore(); // Ignore the newline after the number of scenes

    for (int i = 0; i < numScenes; i++) {
        getline(file, tree[i].description);
    }

    int from, to, weight;

    while (file >> from >> to >> weight) {
        tree[from].transitions.emplace_back(to, weight);
    }

    file.close();
}

vector<int> TrappedNightmare::findDijkstraPath(bool maximize) const {
    int numScenes = tree.size();
    int compareValue = maximize ? numeric_limits<int>::min() : numeric_limits<int>::max();

    vector<int> distance(numScenes, compareValue);
    vector<int> parent(numScenes, -1);
    priority_queue<pair<int, int> > pq;

    distance[0] = 0;
    pq.push(make_pair(0, 0));

    while (!pq.empty()) {
        int currentDistance = -pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        for (const pair<int, int> neighbor : tree[currentNode].transitions) {
            int nextNode = neighbor.first;
            int weight = neighbor.second;

            int adjustedWeight = maximize ? -weight : weight;

            if ((maximize && distance[nextNode] < currentDistance + adjustedWeight) || (!maximize && distance[nextNode] > currentDistance + adjustedWeight)) {
                distance[nextNode] = currentDistance + adjustedWeight;
                parent[nextNode] = currentNode;
                pq.push(make_pair(-distance[nextNode], nextNode));
            }
        }
    }

    vector<int> path;

    for (int node = numScenes - 1; node != -1; node = parent[node]) {
        path.push_back(node);
    }

    reverse(path.begin(), path.end());

    return path;
}

void TrappedNightmare::traversePath(const vector<int>& path) const {

    for (int i = 0; i < path.size() - 1; i++) {
        int currentNode = path[i];

        cout << tree[currentNode].description << endl;
        this_thread::sleep_for(chrono::seconds(2));

        int nextNode = path[i + 1];

        for (const pair<int, int> transition : tree[currentNode].transitions) {
            if (transition.first == nextNode) {
                int intensity = transition.second;

                timeRemaining = max(0, timeRemaining - 50);

                cout << "Time remaining: " << timeRemaining << " seconds.\n";
                this_thread::sleep_for(chrono::seconds(2));
                cout << endl;

                if (timeRemaining <= 0) {
                    cout << "\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣾⣿⣿⣿⣿⣿⣿⣷⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⠟⠋⠁⠀⠀⠈⠙⠻⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⠀⣾⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣷⠀⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⣶⣾⣿⣿⣷⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣾⣿⣿⣷⣶⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⣿⣿⣿⣿⡏⠉⠉⢹⡋⠉⠉⢙⡏⠉⠉⢹⣿⣿⣿⣿⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⣿⣿⣿⣿⡏⢉⠉⢹⠛⠩⡍⠛⡏⠉⠉⢹⣿⣿⣿⣿⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⣿⣿⣿⣿⡇⠐⠀⢸⠀⠀⠃⠀⡇⠀⠂⢸⣿⣿⣿⣿⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⣿⣿⣿⣿⡏⠉⠉⢹⠉⠉⠉⠉⡏⠉⠉⢹⣿⣿⣿⣿⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀\n"
                            "⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀\n";
                    cout << "Time runs out as the nightmare engulfs you... You are trapped forever!\n";
                    return;
                }


                // Describe the intensity of the transition
                if (intensity > 5) {
                    cout << "The air grows heavier as you move, fear gripping your every step...\n";
                } else {
                    cout << "You cautiously proceed, sensing a faint hope ahead...\n";
                }

                this_thread::sleep_for(chrono::seconds(2));

                break;
            }
        }
    }

    cout << tree[path.back()].description << endl;
    this_thread::sleep_for(chrono::seconds(2));

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

    cout << "\nYou've escaped the nightmare!" << endl;
}

void TrappedNightmare::generateDream() const {
    // Handle case where there are no scenes in the tree
    if (tree.empty()) {
        cout << "\n" << dreamerName << ", you find yourself slipping into a dream...\n";
        this_thread::sleep_for(chrono::seconds(2));
        cout << "But nothing happens. You wake up feeling strangely refreshed, as if the nightmare never began.\n";
        return;
    }

    cout << "\n" << dreamerName << ", you find yourself trapped in a labyrinth of terror...\n";
    cout << "You have " << duration << " seconds to escape the trap!\n" << endl;
    this_thread::sleep_for(chrono::seconds(2));

    bool maximize = intensity > 5; // High intensity -> Maximize path
    vector<int> path = findDijkstraPath(maximize);
    traversePath(path);
}

TrappedNightmare::~TrappedNightmare() {}