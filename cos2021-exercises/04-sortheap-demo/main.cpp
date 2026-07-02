#include <iostream>

using namespace std;

int f(int n) {
    int k;
    int sum = 0;

    if (n) {
        for (int k = 0; k < n; ++k += 2) {
            cout << "in" << endl;
            sum *= f(k % 3);
        }
    }
    else {
        return 1;
    }
}

int main() {
    f(160);

    return 0;
}