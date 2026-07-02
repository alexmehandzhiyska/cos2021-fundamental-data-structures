// Online C++ compiler to run C++ program online
#include <iostream>
#include <fstream>

using namespace std;


class ChecksumChecker
{
public:
    ChecksumChecker(const string& fn) : filename(fn) { }

    int compute()
    {
        ifstream inputStream(filename);

        if (inputStream.fail()) {
            cout << "Cannot open file" << endl;
            return 1;
        }

        char currentChar;
        int sum = 0;

        while (inputStream >> currentChar)
        {
            sum += (int)currentChar;
        }

        inputStream.close();
        return sum;
    }
private:
    string filename;
};


int main() {

    ChecksumChecker test("input.txt");
    int sum = test.compute();
    cout << sum << endl;
    return 0;
}